/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:35:19 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/24 15:14:08 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static int	here_doc_read(t_redirection_list *redir_list)
{
	char	*line;

	line = NULL;
	line = readline("here_doc> ");
	if (!line)
	{
		write(redir_list->redirection.fd, "\0", 1);
		error_message(HERE_DOC_EOF_ERROR);
		return (SUCCESS);
	}
	if (g_signal == SIGINT || !ft_strncmp(line,
			redir_list->redirection.filename, ft_strlen(line)))
	{
		free(line);
		return (FAILURE);
	}
	write(redir_list->redirection.fd, line, ft_strlen(line));
	free(line);
	rl_done = 1;
	return (LOOP);
}

int	here_doc(t_redirection_list **redir_list)
{
	int	status;

	(*redir_list)->redirection.fd = open("/tmp/.minishell_here_doc",
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if ((*redir_list)->redirection.fd == -1)
	{
		perror("open");
		return (FAILURE);
	}
	status = here_doc_read(*redir_list);
	signal(SIGINT, SIG_DFL);
	while (status == LOOP && g_signal != SIGINT)
	{
		status = here_doc_read(*redir_list);
	}
	init_signal();
	return (status);
}

int	open_all_here_doc(t_minishell *minishell, t_ast *ast)
{
	t_redirection_list	*redir_list;

	if (!ast)
		return (SUCCESS);
	open_all_here_doc(minishell, ast->left);
	if (ast->type == AST_CMD)
	{
		redir_list = ast->value.redirections;
		while (redir_list)
		{
			if (redir_list->redirection.flag == HERE_DOC)
			{
				if (here_doc(&redir_list) == FAILURE)
					return (FAILURE);
			}
			redir_list = redir_list->next;
		}
	}
	open_all_here_doc(minishell, ast->right);
	return (SUCCESS);
}
