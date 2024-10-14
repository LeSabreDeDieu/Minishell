/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:48:52 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/14 17:00:58 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

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
