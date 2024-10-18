/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:30:56 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/18 12:51:38 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "env.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>

static char	*search_command_on_path(char *name, char *path)
{
	char	*cmd_file;
	char	**tmp;
	char	**move;

	tmp = ft_split(path, ':');
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

char	*get_real_command(char *name, t_minishell *minishell)
{
	char	*real_name;
	char	*path_value;
	t_env	*path;

	path = get_env("PATH");
	if (!path)
		path_value = minishell->data.path;
	else
		path_value = path->value;
	if (!name)
		real_name = (ft_strdup(""));
	else if (is_builtin(name) || !path_value || !*path_value
		|| (ft_strlen(name) >= 2 && ft_strncmp(name, "./", 2) == 0)
		|| (ft_strlen(name) >= 2 && ft_strncmp(name, "/", 1) == 0))
		real_name = (ft_strdup(name));
	else
		real_name = search_command_on_path(name, path_value);
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
	else if (is_exact_name(name, "export"))
		status = export_command(argc, argv);
	else if (is_exact_name(name, "unset"))
		status = unset_command(minishell, argc, argv);
	else if (is_exact_name(name, "pwd"))
		status = pwd_command(argc, argv);
	else if (is_exact_name(name, "history"))
		status = history_command(minishell, argc, argv);
	return (status);
}
