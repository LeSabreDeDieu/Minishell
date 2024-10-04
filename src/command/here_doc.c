/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:35:19 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/04 17:11:37 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

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
	if (strcmp(line, redir_list->redirection.filename) == 0)
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
			O_CREAT | O_RDWR | O_APPEND, 0644);
	if (redir_list->redirection.fd == -1)
	{
		free(here_doc_name);
		perror("open");
		return (FAILURE);
	}
	free(here_doc_name);
	return (SUCCESS);
}

int	open_here_doc(t_minishell *minishell, t_ast_value *ast_value, int itterdoc)
{
	t_redirection_list	*redir_list;
	pid_t				pid;
	int					status;
	char				*itterdoc_str;
	char				*here_doc_name;

	redir_list = ast_value->redirections;
	while (redir_list)
	{
		if (redir_list->redirection.flag == HERE_DOC)
		{
			if (create_and_open_heredoc_file(redir_list, itterdoc) == FAILURE)
				return (FAILURE);
			pid = fork();
			if (pid == -1)
				return (FAILURE);
			if (pid == 0)
				(signal(SIGINT, &ft_signal_heredoc), signal(SIGQUIT, SIG_IGN),
					here_doc(minishell, redir_list));
			else
			{
				waitpid(pid, &status, 0);
				itterdoc_str = ft_itoa(itterdoc);
				here_doc_name = ft_strjoin(HERE_DOC_PATH, itterdoc_str);
				free(itterdoc_str);
				free(redir_list->redirection.filename);
				redir_list->redirection.filename = here_doc_name;
				free(here_doc_name);
			}
			close(redir_list->redirection.fd);
		}
		redir_list = redir_list->next;
	}
	return (SUCCESS);
}

int	open_all_here_doc(t_minishell *minishell, t_ast *ast, int itterdoc)
{
	if (!ast)
		return (SUCCESS);
	open_all_here_doc(minishell, ast->left, itterdoc);
	if (ast->type == AST_CMD || ast->type == AST_SUBSHELL)
	{
		++itterdoc;
		if (open_here_doc(minishell, &ast->value, itterdoc) == FAILURE)
		{
			return (FAILURE);
		}
	}
	open_all_here_doc(minishell, ast->right, itterdoc);
	return (SUCCESS);
}
