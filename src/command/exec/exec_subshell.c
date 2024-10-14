/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:29:24 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/14 15:50:48 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "env.h"
#include "ms_signal.h"
#include <fcntl.h>
#include <stdio.h>

int	handle_subshell_redirections(t_minishell *data, t_ast_value *value)
{
	if (open_all_redirection(value->redirections) == FAILURE)
		exit(errno);
	close_dup_standard(value);
	if (dup_all_redir(value->redirections) == -1)
	{
		close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR | UNLINK);
		free_minishell(data, FREE_ALL);
		exit(ENOENT);
	}
	return (SUCCESS);
}

void	execute_in_subshell(t_minishell *data, t_ast_value *value)
{
	char		*prompt;
	int			status;

	if (handle_subshell_redirections(data, value) == FAILURE)
		return ;
	prompt = ft_substr(value->name, 1, ft_strlen(value->name) - 2);
	if (!prompt)
	{
		close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR | UNLINK);
		free_minishell(data, FREE_ALL);
		exit(ENOMEM);
	}
	free_minishell(data, FREE_AST | FREE_TOKEN);
	status = traitement(data, prompt);
	free_minishell(data, FREE_ALL);
	exit(status);
}

int	fork_subshell(t_minishell *data, t_ast_value *value)
{
	value->pid = fork();
	if (value->pid < 0)
	{
		data->current_status = errno;
		error_message_command("fork", strerror(errno));
		return (FAILURE);
	}
	if (!value->pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		g_signal = 0;
		execute_in_subshell(data, value);
	}
	return (SUCCESS);
}

int	execute_subshell(t_minishell *data, t_ast_value *value)
{
	int	old_errno;

	if (!value->name)
	{
		open_all_redirection(value->redirections);
		old_errno = errno;
		close_all_redir(value, CLOSE_FD_REDIR);
		return (data->current_status = old_errno);
	}
	dup_standard(value);
	if (fork_subshell(data, value) == FAILURE)
		return (FAILURE);
	close_all_redir(value, CLOSE_DUP_STD | CLOSE_PIPE);
	return (SUCCESS);
}
