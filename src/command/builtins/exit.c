/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:11:15 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/18 16:38:41 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "tokens.h"
#include "ast.h"
#include <stdio.h>

char	is_number(const char *str)
{
	const char *move;

	move = str;
	if (*move == '-')
		++move;
	while(*move && ft_isdigit(*move))
		++move;
	return (*move == 0);
}

int		exit_command(t_minishell *minishell, int argc, char *argv[])
{
	unsigned char	status;

	status = minishell->current_status;
	if (argc >= 2)
	{
		if(!is_number(argv[1]))
			return (245);
		status = ft_atoi(argv[1]);
	}
	free_minishell(minishell, FREE_ALL);
	printf("\033]0;exit\007");
	printf("status: %d\n", status);
	exit(status);
}
