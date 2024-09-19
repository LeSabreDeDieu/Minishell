/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:30:56 by gcaptari          #+#    #+#             */
/*   Updated: 2024/09/19 14:10:56 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "env.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>

static bool	is_exact_name(char *name, char *equal)
{
	size_t	len;
	size_t	len_eq;

	len = ft_strlen(name);
	len_eq = ft_strlen(equal);
	return (ft_strncmp(name, equal, len) == 0 && ft_strncmp(equal, name,
			len_eq) == 0);
}

bool	is_builtin(char *name)
{
	return (is_exact_name(name, "echo") || is_exact_name(name, "cd")
		|| is_exact_name(name, "exit") || is_exact_name(name, "env")
		|| is_exact_name(name, "unset"));
}

static char	*special_cmd_join(char *path, char *name)
{
	char	*cmd_path;
	char	*cmd_file;

	cmd_path = ft_strjoin(path, "/");
	if (!cmd_path)
		return (NULL);
	cmd_file = ft_strjoin(cmd_path, name);
	free(cmd_path);
	return (cmd_file);
}

static char	*search_command_on_path(char *name, t_env *path)
{
	char	*cmd_file;
	char	**tmp;
	char	**move;

	tmp = ft_split(path->value, ':');
	if (!tmp)
		return (NULL);
	move = tmp;
	while (*move)
	{
		cmd_file = special_cmd_join(*move, name);
		if (!cmd_file && ++move)
			continue ;
		if (access(cmd_file, F_OK | X_OK) == 0)
			break ;
		(free(cmd_file), cmd_file = NULL);
		++move;
	}
	if (!cmd_file)
		cmd_file = ft_strdup(name);
	free_str_tab(tmp);
	return (cmd_file);
}

char	*get_real_command(char *name)
{
	char	*real_name;
	t_env	*path;

	path = get_env("PATH");
	if (!name)
		real_name = (ft_strdup(""));
	else if (is_builtin(name) || !path || !*path->value || (ft_strlen(name) >= 2
			&& ft_strncmp(name, "./", 2) == 0) || (ft_strlen(name) >= 2
			&& ft_strncmp(name, "/", 1) == 0))
		real_name = (ft_strdup(name));
	else
		real_name = search_command_on_path(name, path);
	return (real_name);
}

int	exceve_builtins(t_minishell *minishell, char *name, int argc, char *argv[])
{
	int	status;

	status = ENOENT;
	if (is_exact_name(name, "echo"))
		status = echo_command(argc, argv);
	else if (is_exact_name(name, "cd"))
		status = cd_command(argc, argv);
	else if (is_exact_name(name, "exit"))
		status = exit_command(minishell, argc, argv);
	else if (is_exact_name(name, "env"))
		status = env_command(argc, argv);
	else if (is_exact_name(name, "unset"))
		status = unset_command(argc, argv);
	return (status);
}
static void	fork_error_message(char *error)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": fork: ", 2);
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

int	open_all_redirection(t_redirection_list *list)
{
	t_redirection_list	*current;
	int					status;

	status = 0;
	current = list;
	while (current)
	{
		if (current->redirection.filename != NULL)
		{
			if ((int)current->redirection.flag == WRITE)
			{
				current->redirection.fd = open(current->redirection.filename,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (current->redirection.fd == -1)
				{
					command_error_message(current->redirection.filename,
						strerror(errno));
					status = -1;
					break ;
				}
			}
			else if ((int)current->redirection.flag == READ)
			{
				current->redirection.fd = open(current->redirection.filename,
						O_RDONLY, 0644);
				if (current->redirection.fd == -1)
				{
					command_error_message(current->redirection.filename,
						strerror(errno));
					status = -1;
					break ;
				}
			}
		}
		current = current->next;
	}
	return (status);
}

int	dup_all_redir(t_redirection_list *list)
{
	t_redirection_list	*current;
	int					status;

	current = list;
	status = 0;
	while (current)
	{
		if (current->redirection.filename != NULL)
		{
			if ((int)current->redirection.flag == WRITE
				&& current->redirection.fd != -1)
			{
				dup2(current->redirection.fd, STDOUT_FILENO);
				close(current->redirection.fd);
			}
			else if ((int)current->redirection.flag == READ
				&& current->redirection.fd != -1)
			{
				dup2(current->redirection.fd, STDIN_FILENO);
				close(current->redirection.fd);
			}
			else if ((int)current->redirection.flag == READ
				&& current->redirection.fd == -1)
			{
				status = -1;
				break ;
			}
			else if ((int)current->redirection.flag == WRITE
				&& current->redirection.fd == -1)
			{
				status = -1;
				break ;
			}
		}
		current = current->next;
	}
	return (status);
}

void	close_all_redir(t_ast_value *value, int action)
{
	t_redirection_list	*current;

	// printf("name : %s\nfd_in : %p => %i, fd_out : %p => %i\n",value->name, &value->fd_in, value->fd_in, &value->fd_out, value->fd_out);
	if (action & CLOSE_DUP_STD)
	{
		if (value->fd_in != -1)
			close(value->fd_in);
		if (value->fd_out != -1)
			close(value->fd_out);
	}
	if (action & CLOSE_PIPE)
		close(value->fd_out);
	if (action & CLOSE_FD_REDIR)
	{
		current = value->redirections;
		while (current)
		{
			if (current->redirection.filename != NULL
				&& current->redirection.fd != -1)
				close(current->redirection.fd);
			current = current->next;
		}
	}
}

int	safe_dup_all_redir(t_minishell *data, t_ast_value *value, int action_mini,
		int action_redir)
{
	if (dup_all_redir(value->redirections) == -1)
	{
		if (action_mini != -1)
			free_minishell(data, action_mini);
		if (action_redir != -1)
			close_all_redir(value, action_redir);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	dup_standard(t_ast_value *value)
{
	value->fd_in = dup(STDIN_FILENO);
	value->fd_out = dup(STDOUT_FILENO);
}

void	close_dup_standard(t_ast_value *value)
{
	if (value->fd_in != -1)
	{
		dup2(value->fd_in, STDIN_FILENO);
		close(value->fd_in);
	}
	if (value->fd_out != -1)
	{
		dup2(value->fd_out, STDOUT_FILENO);
		close(value->fd_out);
	}
}

int	execute_simple(t_minishell *minishell, t_ast_value *value)
{
	char	*path;
	char	**envp;

	dup_standard(value);
  	if (value->name == NULL || value->argc == 0)
    return (ENOENT);
	if (is_builtin(value->name))
	{
		if (dup_all_redir(value->redirections) == 0)
			minishell->current_status = exceve_builtins(minishell, value->name, value->argc,
					value->argv);
		else
			minishell->current_status = ENOENT;
		close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR);
		return (minishell->current_status);
	}
	value->pid = fork();
	if (value->pid < 0)
	{
		fork_error_message(strerror(errno));
		minishell->current_status = errno;
		return (-1);
	}
	if (!value->pid)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (open_all_redirection(value->redirections) == FAILURE)
			exit(errno);
		close_dup_standard(value);
		path = get_real_command(value->name);
		if (!path)
			(fork_error_message("Malloc failled"), exit(ENOMEM));
		else if (safe_dup_all_redir(minishell, value, FREE_ALL, CLOSE_DUP_STD | CLOSE_FD_REDIR) == -1)
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
	close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR);
	return (0);
}

__pid_t	execute_pipe_last(t_minishell *minishell, int *pipe_in,
		t_ast_value *value, char *envp[])
{
	int		state;
	char	*path;
	int		test;

	test = dup(STDOUT_FILENO);
	value->fd_out = test;
	value->pid = fork();
	if (value->pid < 0)
	{
		fork_error_message(strerror(errno));
		return (-1);
	}
	if (!value->pid)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	  if (open_all_redirection(value->redirections) == FAILURE)
		  exit(errno);
		dup2(value->fd_out, STDOUT_FILENO);
		close(value->fd_out);
		if (*pipe_in != -1)
		{
			dup2(*pipe_in, STDIN_FILENO);
			close(*pipe_in);
		}
		if (safe_dup_all_redir(minishell, value, FREE_ALL,
				CLOSE_FD_REDIR | CLOSE_DUP_STD) == -1)
			exit(ENOENT);
		if (is_builtin(value->name))
		{
			state = exceve_builtins(minishell, value->name, value->argc,
					value->argv);
			close_all_redir(value, CLOSE_FD_REDIR | CLOSE_DUP_STD);
			free_minishell(minishell, FREE_ALL);
			exit(state);
		}
		path = get_real_command(value->name);
		if (!path)
			(fork_error_message("Malloc failled"), exit(ENOMEM));
		if (execve(path, value->argv, envp) != 0)
			command_error_message(value->name, "Command not found");
		free(path);
		close_all_redir(value, CLOSE_FD_REDIR | CLOSE_DUP_STD);
		free_minishell(minishell, FREE_ALL);
		exit(errno);
	}
	if (*pipe_in != -1)
		close(*pipe_in);
	close_all_redir(value, CLOSE_FD_REDIR | CLOSE_DUP_STD);
	return (value->pid);
}

int	execute_subshell(t_minishell *data, t_ast_value *value)
{
	char	*prompt;


	dup_standard(value);
	value->pid = fork();
	if (value->pid < 0)
	{
		data->current_status = errno;
		fork_error_message(strerror(errno));
		return (FAILURE);
	}
	if (!value->pid)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (open_all_redirection(value->redirections) == FAILURE)
			exit(errno);
		close_dup_standard(value);
		if (dup_all_redir(value->redirections) == -1)
		{
			close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR);
			free_minishell(data, FREE_AST | FREE_ENV | FREE_TOKEN | FREE_PIPE);
			exit(ENOENT);
		}
		prompt = ft_strdup(value->name);
		free_minishell(data, FREE_AST | FREE_PIPE);
		traitement(data, prompt);
		free_minishell(data, FREE_AST | FREE_ENV | FREE_TOKEN | FREE_PIPE);
		exit(errno);
	}
	close_all_redir(value, CLOSE_DUP_STD | CLOSE_PIPE);
	return (0);
}
