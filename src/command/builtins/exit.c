/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:11:15 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/18 12:28:13 by sgabsi           ###   ########.fr       */
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
	if (argc >= 2 && !is_number(argv[1]))
	{
		ft_putstr_fd("exit\n\033[0m\007\033[1 q\007", STDOUT_FILENO);
		error_message_command_with_arg("exit", argv[1],
			"numeric argument required");
		free_minishell(minishell, FREE_ALL);
		exit(2);
	}
	if (argc > 2)
	{
		error_message_command("exit", "too many arguments");
		return (1);
	}
	else if (argc == 2)
		status = ft_atoi(argv[1]);
	free_minishell(minishell, FREE_ALL);
	ft_putstr_fd("exit\n\033[0m\007\033[1 q\007", STDOUT_FILENO);
	exit(status);
}
