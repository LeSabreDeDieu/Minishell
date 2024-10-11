/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:20:20 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/11 17:53:21 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "env.h"
#include "ms_signal.h"
#include <fcntl.h>
#include <stdio.h>


int	execute_builout(t_minishell *minishell, t_ast_value *value)
{
	int 	state;
	char	*path;
	char	**envp;

	path = get_real_command(value->name, minishell);
	if (!path)
		(error_message_command("fork", "Malloc failled"),
			free_minishell(minishell, FREE_ALL), exit(ENOMEM));
	envp = env_to_tab();
	if (!envp)
		(error_message_command("fork", "Malloc failled"),
			free_minishell(minishell, FREE_ALL), exit(ENOMEM));
	if (execve(path, value->argv, envp) != 0)
		(error_message_command(value->name, COMMAND_NOT_FOUND), errno = 127);
	state = errno;
	(free(path), free_str_tab(envp));
	return (state);
}
