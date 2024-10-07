/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:34:57 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/04 17:18:53 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "env.h"

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
	path = get_real_command(value->name, minishell);
	if (!path)
		(error_message_command("fork", "Malloc failled"), free_minishell(minishell, FREE_ALL), exit(ENOMEM));
	else if (safe_dup_all_redir(minishell, value, FREE_ALL,
			CLOSE_DUP_STD | CLOSE_FD_REDIR) == -1)
	{
		free(path);
		exit(ENOENT);
	}
		envp = env_to_tab();
		if (!envp)
			(error_message_command("fork", "Malloc failled"), free_minishell(minishell, FREE_ALL), exit(ENOMEM));
	envp = env_to_tab();
	if (execve(path, value->argv, envp) != 0)
		error_message_command(value->name, COMMAND_NOT_FOUND);
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
		error_message_command("fork", strerror(errno));
		minishell->current_status = errno;
		return (-1);
	}
	if (!value->pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		if (open_all_redirection(value->redirections) == FAILURE)
		{
			close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR);
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
