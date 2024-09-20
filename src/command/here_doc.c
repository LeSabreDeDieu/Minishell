/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:35:19 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/20 10:22:16 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static int	here_doc_read(t_redirection_list *redir_list)
{
	char	*line;

	line = NULL;
	line = readline("> ");
	if (g_signal == SIGINT || !ft_strncmp(line,
			redir_list->redirection.filename, ft_strlen(line)))
	{
		free(line);
		return (FAILURE);
	}
	if (!line)
	{
		write(redir_list->redirection.fd, "\0", 1);
		error_message(HERE_DOC_EOF_ERROR);
		return (FAILURE);
	}
	write(redir_list->redirection.fd, line, ft_strlen(line));
	free(line);
	return (SUCCESS);
}

void	here_doc(t_redirection_list **redir_list)
{
	(*redir_list)->redirection.fd = open("/tmp/.minishell_here_doc",
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if ((*redir_list)->redirection.fd == -1)
	{
		perror("open");
		return ;
	}
	while (1)
	{
		if (here_doc_read((*redir_list)) == FAILURE)
			break ;
	}
}
