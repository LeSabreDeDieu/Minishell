/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:34:57 by gcaptari          #+#    #+#             */
/*   Updated: 2024/09/23 11:56:25 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "env.h"
#include <fcntl.h>
#include <stdio.h>

static int	handle_builtin(t_minishell *minishell, t_ast_value *value)
{
	if (open_all_redirection(value->redirections) == FAILURE)
	{
		close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR);
		return (minishell->current_status = ENOENT);
	}
	if (dup_all_redir(value->redirections) == 0)
		minishell->current_status = exceve_builtins(minishell, value->name,
				value->argc, value->argv);
	else
		minishell->current_status = ENOENT;
	close_dup_standard(value);
	close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR);
	return (minishell->current_status);
}

static int	handle_child_process(t_minishell *minishell, t_ast_value *value)
{
	char	**envp;
	char	*path;

	close_dup_standard(value);
	path = get_real_command(value->name);
	if (!path)
		(fork_error_message("Malloc failed"), exit(ENOMEM));
	else if (safe_dup_all_redir(minishell, value, FREE_ALL,
			CLOSE_DUP_STD | CLOSE_FD_REDIR) == -1)
	{
		free(path);
		exit(ENOENT);
	}
	envp = env_to_tab();
	if (execve(path, value->argv, envp) != 0)
		command_error_message(value->name, "Command not found");
	free_str_tab(envp);
	free(path);
	close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR);
	free_minishell(minishell, FREE_ALL);
	exit(errno);
}

static int	handle_fork(t_minishell *minishell, t_ast_value *value)
{

	value->pid = fork();
	if (value->pid < 0)
	{
		fork_error_message(strerror(errno));
		minishell->current_status = errno;
		return (-1);
	}
	if (!value->pid)
		handle_child_process(minishell, value);
	close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR);
	return (0);
}

int	execute_simple(t_minishell *minishell, t_ast_value *value)
{
	dup_standard(value);
	if (value->name == NULL || value->argc == 0)
		return (ENOENT);
	if (is_builtin(value->name))
		return (handle_builtin(minishell, value));
	return (handle_fork(minishell, value));
}
