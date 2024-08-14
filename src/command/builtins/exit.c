/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:11:15 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/14 14:46:06 by gcaptari         ###   ########.fr       */
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
	int	status;

	status = 0;
	if (argc >= 2)
	{
		if(!is_number(argv[1]))
			return (245);
		status = ft_atoi(argv[1]);
	}

	printf("exit\n");
	free_on_children(minishell);
	exit(status);
}
