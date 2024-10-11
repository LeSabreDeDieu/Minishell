/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:34:57 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/11 18:25:16 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "env.h"
#include "ms_signal.h"

static int	handle_builtin(t_minishell *minishell, t_ast_value *value)
{
	if (open_all_redirection(value->redirections) == FAILURE)
	{
		close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR | UNLINK);
		return (minishell->current_status = ENOENT);
	}
	if (dup_all_redir(value->redirections) == 0)
		minishell->current_status = exceve_builtins(minishell, value->name,
				value->argc, value->argv);
	else
		minishell->current_status = ENOENT;
	close_dup_standard(value);
	close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR | UNLINK);
	return (minishell->current_status);
}

static int	handle_child_process(t_minishell *minishell, t_ast_value *value)
{
	int	status;

	close_dup_standard(value);
	if ((ft_strncmp(value->name, "./", 2) == 0 || ft_strncmp(value->name, "/",
				1) == 0) && access(value->name, F_OK) != 0)
	{
		(error_message_with_arg(value->name, strerror(ENOENT)),
			free_minishell(minishell, FREE_ALL), exit(ENOENT));
	}
	if (safe_dup_all_redir(minishell, value, FREE_ALL,
			CLOSE_DUP_STD | CLOSE_FD_REDIR | UNLINK) == -1)
	{
		exit(ENOENT);
	}
	status = execute_builout(minishell, value);
	close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR | UNLINK);
	free_minishell(minishell, FREE_ALL);
	exit(status);
}

static int	handle_fork(t_minishell *minishell, t_ast_value *value)
{
	value->pid = fork();
	if (value->pid < 0)
	{
		error_message_command("fork", strerror(errno));
		minishell->current_status = errno;
		return (-1);
	}
	if (!value->pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (open_all_redirection(value->redirections) == FAILURE)
		{
			close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR | UNLINK);
			free_minishell(minishell, FREE_ALL);
			exit(errno);
		}
		handle_child_process(minishell, value);
	}
	close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR);
	return (0);
}

int	execute_simple(t_minishell *minishell, t_ast_value *value)
{
	int	old_errno;

	dup_standard(value);
	if (!value->name)
	{
		open_all_redirection(value->redirections);
		old_errno = errno;
		close_all_redir(value, CLOSE_FD_REDIR);
		return (minishell->current_status = errno);
	}
	if (is_builtin(value->name))
		return (handle_builtin(minishell, value));
	return (handle_fork(minishell, value));
}
