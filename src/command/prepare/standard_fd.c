/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:48:52 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/15 11:19:17 by gcaptari         ###   ########.fr       */
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
		dup2(value->fd_in, STDIN_FILENO);
	if (value->fd_out != -1)
		dup2(value->fd_out, STDOUT_FILENO);
	close_all_redir(value, CLOSE_DUP_STD);
}
