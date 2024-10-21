/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:20:20 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/21 17:58:57 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "env.h"
#include "ms_signal.h"
#include <fcntl.h>
#include <stdio.h>

static bool	is_dir(char *path)
{
	struct stat	statbuf;

	if (ft_strncmp(path, ".", 1) != 0
		&& ft_strncmp(path, "/", 1) != 0)
		return (false);
	if (stat(path, &statbuf) == -1)
		return (false);
	return (S_ISDIR(statbuf.st_mode));
}

int	execute_builout(t_minishell *minishell, t_ast_value *value)
{
	int		state;
	char	*path;
	char	**envp;

	if (is_dir(value->name))
	{
		error_message_command(value->name, IS_A_DIRECTORY);
		return (IS_DIR_ERROR);
	}
	path = get_real_command(value->name, minishell);
	if (!path)
		return (error_message_command("fork", MALLOC_FAILLED), ENOMEM);
	envp = env_to_tab();
	if (!envp)
		return (error_message_command("fork", MALLOC_FAILLED), free(path),
			ENOMEM);
	if (execve(path, value->argv, envp) != 0)
		(error_message_command(value->name, COMMAND_NOT_FOUND),
			errno = COMMAND_NOT_FOUND_ERROR);
	state = errno;
	(free(path), free_str_tab(envp));
	return (state);
}
