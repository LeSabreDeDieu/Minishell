/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:11:15 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/11 09:49:11 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <stdio.h>

char	is_number(const char *str)
{
	const char	*move;

	move = str;
	if (*move == '-')
		++move;
	while (*move && ft_isdigit(*move))
		++move;
	return (*move == 0);
}

int	exit_command(t_minishell *minishell, int argc, char *argv[])
{
	unsigned char	status;

	status = minishell->current_status;
	if (argc == 1)
	{
		free_minishell(minishell, FREE_ALL);
		ft_putstr_fd("exit\n\033[0m\007\033[1 q\007", STDOUT_FILENO);
		exit(status);
	}
	if (!is_number(argv[1]))
	{
		error_message_command_with_arg("exit", argv[1],
			"numeric argument required");
		exit(2);
	}
	if (argc > 2)
		return (ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO), 1);
	else if (argc == 2)
		status = ft_atoi(argv[1]);
	free_minishell(minishell, FREE_ALL);
	ft_putstr_fd("exit\n\033[0m\007\033[1 q\007", STDOUT_FILENO);
	exit(status);
	return (status);
}
