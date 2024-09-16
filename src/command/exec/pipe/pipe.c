
#include "ast.h"
#include "env.h"
#include "command.h"
#include <fcntl.h>
#include <stdio.h>

static void	fork_error_message(char *error)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("fork: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}
static void	command_error_message(char *command, char *error)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void execution_cmd_pipe(t_minishell *minishell, t_ast_value *value)
{
	int		state;
	char	*path;
	char	**envp;

	if (is_builtin(value->name))
	{
		state = exceve_builtins(minishell, value->name, value->argc,
				value->argv);
		close_all_redir(value, CLOSE_FD_REDIR);
		free_minishell(minishell, FREE_ALL);
		exit(state);
	}
	path = get_real_command(value->name);
	if (!path)
		(fork_error_message("Malloc failled"), exit(ENOMEM));
	envp = env_to_tab();
	if (!envp)
		(fork_error_message("Malloc failled"), exit(ENOMEM));
	if (execve(path, value->argv, envp) != 0)
		command_error_message(value->name, "Command not found");
	(free(path), free(envp));
	close_all_redir(value, CLOSE_FD_REDIR | CLOSE_DUP_STD);
	free_minishell(minishell, FREE_ALL);
	exit(errno);
}

void	execute_pipe(t_minishell *minishell, int *pipe_in, t_ast_value *value)
{
	if (open_all_redirection(value->redirections) == FAILURE)
		return ;
	create_pipe(value);
	value->pid = fork();
	if (value->pid < 0)
		return (fork_error_message(strerror(errno)));
	if (!value->pid)
	{
		close(value->fd_in);
		if (*pipe_in != -1)
			(dup2(*pipe_in, STDIN_FILENO), close(*pipe_in));
		dup2(value->fd_out, STDOUT_FILENO);
		close(value->fd_out);
		if (safe_dup_all_redir(minishell, value, FREE_ALL, CLOSE_DUP_STD | CLOSE_FD_REDIR) == -1)
			exit(ENOENT);
		execution_cmd_pipe(minishell, value);
	}
	if(*pipe_in != -1)
		close(*pipe_in);
	close_all_redir(value, CLOSE_FD_REDIR | CLOSE_PIPE);
	*pipe_in = value->fd_in;
}
