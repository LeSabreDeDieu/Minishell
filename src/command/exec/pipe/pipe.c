/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:29:31 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/14 11:07:06 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "env.h"
#include "ms_signal.h"
#include <fcntl.h>
#include <stdio.h>

void	execution_cmd_pipe(t_minishell *minishell, t_ast_value *value)
{
	int		state;

	state = 0;
	if (value->name)
	{
		if (is_builtin(value->name))
			state = exceve_builtins(minishell, value->name, value->argc,
					value->argv);
		else
			state = execute_builout(minishell, value);
	}
	close_all_redir(value, CLOSE_FD_REDIR | CLOSE_DUP_STD | UNLINK);
	(free_minishell(minishell, FREE_ALL), exit(state));
}

void	execute_pipe(t_minishell *minishell, int *pipe_in, t_ast_value *value)
{
	create_pipe(value);
	value->pid = fork();
	if (value->pid < 0)
		return (error_message_command("fork", strerror(errno)));
	if (!value->pid)
	{
		if (open_all_redirection(value->redirections) == FAILURE)
			(close_all_redir(value, CLOSE_FD_REDIR | CLOSE_DUP_STD | UNLINK),
				exit(errno));
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		close(value->fd_in);
		if (*pipe_in != -1)
			(dup2(*pipe_in, STDIN_FILENO), close(*pipe_in));
		dup2(value->fd_out, STDOUT_FILENO);
		close(value->fd_out);
		if (safe_dup_all_redir(minishell, value, FREE_ALL,
				CLOSE_DUP_STD | CLOSE_FD_REDIR | UNLINK) == -1)
			exit(ENOENT);
		execution_cmd_pipe(minishell, value);
	}
	if (*pipe_in != -1)
		close(*pipe_in);
	close_all_redir(value, CLOSE_FD_REDIR | CLOSE_PIPE);
	*pipe_in = value->fd_in;
}
void	execute_pipe_sub(t_minishell *minishell, int *pipe_in, t_ast_value *value)
{
	create_pipe(value);
	value->pid = fork();
	if (value->pid < 0)
		return (error_message_command("fork", strerror(errno)));
	if (!value->pid)
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		close(value->fd_in);
		if (*pipe_in != -1)
			(dup2(*pipe_in, STDIN_FILENO), close(*pipe_in));
		dup2(value->fd_out, STDOUT_FILENO);
		close(value->fd_out);
		execute_in_subshell(minishell, value);
	}
	if (*pipe_in != -1)
		close(*pipe_in);
	close_all_redir(value, CLOSE_FD_REDIR | CLOSE_PIPE);
	*pipe_in = value->fd_in;
}

void	execute_pipe_last(t_minishell *minishell, int *pipe_in,
		t_ast_value *value)
{
	value->fd_out = dup(STDOUT_FILENO);
	value->pid = fork();
	if (value->pid < 0)
	{
		error_message_command("fork", strerror(errno));
		return ;
	}
	if (!value->pid)
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		if (open_all_redirection(value->redirections) == FAILURE)
			exit(errno);
		if (*pipe_in != -1)
			(dup2(*pipe_in, STDIN_FILENO), close(*pipe_in));
		dup2(value->fd_out, STDOUT_FILENO);
		close(value->fd_out);
		if (safe_dup_all_redir(minishell, value, FREE_ALL,
				CLOSE_DUP_STD | CLOSE_FD_REDIR | UNLINK) == -1)
			exit(ENOENT);
		execution_cmd_pipe(minishell, value);
	}
	if (*pipe_in != -1)
		close(*pipe_in);
	close_all_redir(value, CLOSE_FD_REDIR | CLOSE_DUP_STD);
}
void	execute_pipe_sub_last(t_minishell *minishell, int *pipe_in, t_ast_value *value)
{
	value->fd_out = dup(STDOUT_FILENO);
	value->fd_in = -1;
	value->pid = fork();
	if (value->pid < 0)
		return (error_message_command("fork", strerror(errno)));
	if (!value->pid)
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		if (*pipe_in != -1 && *pipe_in != 0)
			(dup2(*pipe_in, STDIN_FILENO), close(*pipe_in));
		dup2(value->fd_out, STDOUT_FILENO);
		close(value->fd_out);
		execute_in_subshell(minishell, value);
	}
	if (*pipe_in != -1)
		close(*pipe_in);
	close_all_redir(value, CLOSE_FD_REDIR | CLOSE_DUP_STD);
}
