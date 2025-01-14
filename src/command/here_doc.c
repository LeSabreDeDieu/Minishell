/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:35:19 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/14 17:13:21 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static int	here_doc_read(t_redirection_list *redir_list)
{
	char	*line;

	line = readline("heredoc> ");
	if (g_signal == SIGINT)
		return (free(line), FAILURE);
	if (line == NULL)
	{
		write(redir_list->redirection.fd, "\0", 1);
		error_message(HERE_DOC_EOF_ERROR);
		return (SUCCESS);
	}
	if (*line == '\0')
		return (free(line), LOOP);
	if (ft_strlen(line) == ft_strlen(redir_list->redirection.filename)
		&& ft_strncmp(line, redir_list->redirection.filename,
			ft_strlen(line)) == 0)
		return (free(line), FAILURE);
	ft_putendl_fd(line, redir_list->redirection.fd);
	return (free(line), LOOP);
}

int	here_doc(t_minishell *minishell, t_redirection_list *redir_list)
{
	int	status;

	status = here_doc_read(redir_list);
	while (status == LOOP && g_signal != SIGINT)
	{
		minishell->is_here_doc = true;
		status = here_doc_read(redir_list);
		if (status == FAILURE)
			break ;
	}
	minishell->is_here_doc = false;
	free_minishell(minishell, FREE_ALL);
	if (g_signal == SIGINT)
		exit(130);
	exit(errno);
}

int	create_and_open_heredoc_file(t_redirection_list *redir_list, int itterdoc)
{
	char	*itterdoc_str;
	char	*here_doc_name;

	itterdoc_str = ft_itoa(itterdoc);
	here_doc_name = ft_strjoin(HERE_DOC_PATH, itterdoc_str);
	free(itterdoc_str);
	redir_list->redirection.fd = open(here_doc_name,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redir_list->redirection.fd == -1)
	{
		free(here_doc_name);
		perror("open");
		return (FAILURE);
	}
	free(here_doc_name);
	return (SUCCESS);
}

int	open_here_doc(t_minishell *minishell, t_ast_value *ast_value, int *itterdoc)
{
	t_redirection_list	*redir_list;

	redir_list = ast_value->redirections;
	while (redir_list)
	{
		if (redir_list->redirection.flag == HERE_DOC)
		{
			++(*itterdoc);
			if (fork_hd(minishell, redir_list, *itterdoc) == FAILURE)
				return (FAILURE);
		}
		redir_list = redir_list->next;
	}
	return (SUCCESS);
}

int	open_all_here_doc(t_minishell *minishell, t_ast *ast, int *itterdoc)
{
	if (!ast)
		return (SUCCESS);
	if (open_all_here_doc(minishell, ast->right, itterdoc) == FAILURE)
		return (FAILURE);
	if (ast->type == AST_CMD || ast->type == AST_SUBSHELL)
	{
		if (open_here_doc(minishell, &ast->value, itterdoc) == FAILURE)
		{
			return (FAILURE);
		}
	}
	if (open_all_here_doc(minishell, ast->left, itterdoc) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
