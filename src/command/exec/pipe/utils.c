/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:06:01 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/15 11:28:15 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "env.h"
#include <fcntl.h>
#include <stdio.h>

int	create_pipe(t_ast_value *value)
{
	int	fd[2];

	if (pipe(fd) == 0)
	{
		value->fd_in = fd[STDIN_FILENO];
		value->fd_out = fd[STDOUT_FILENO];
		return (SUCCESS);
	}
	return (FAILURE);
}
