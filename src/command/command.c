/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:30:56 by gcaptari          #+#    #+#             */
/*   Updated: 2024/09/23 11:51:29 by gcaptari         ###   ########.fr       */
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
void	fork_error_message(char *error)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": fork: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}
void	command_error_message(char *command, char *error)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}
