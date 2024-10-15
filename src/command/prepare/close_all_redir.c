/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:45:46 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/15 12:58:45 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	close_std_fds(t_ast_value *value)
{
	if (value->fd_in != -1)
	{
		if (close(value->fd_in) == -1)
			error_message_command("standard", strerror(errno));
		value->fd_in = -1;
	}
	if (value->fd_out != -1)
	{
		if (close(value->fd_out) == -1)
			error_message_command("standard", strerror(errno));
		value->fd_out = -1;
	}
}

void	close_pipe_fds(t_ast_value *value)
{
	if (value->fd_out != -1)
	{
		if (close(value->fd_out) == -1)
			error_message_command("pipe", strerror(errno));
		value->fd_out = -1;
	}
}

void	close_redirection_fds(t_redirection_list *list, bool is_unlik)
{
	t_redirection_list	*current;

	current = list;
	while (current)
	{
		if (current->redirection.fd != -1)
		{
			if (close(current->redirection.fd) == -1)
				error_message(strerror(errno));
			else
				current->redirection.fd = -1;
		}
		if (is_unlik && current->redirection.flag == HERE_DOC
			&& current->redirection.filename != NULL
			&& unlink(current->redirection.filename) == -1)
			error_message_command(current->redirection.filename,
				strerror(errno));
		current = current->next;
	}
}

void	close_all_redir(t_ast_value *value, int action)
{
	if (action & CLOSE_DUP_STD)
		close_std_fds(value);
	if (action & CLOSE_PIPE)
		close_pipe_fds(value);
	if (action & CLOSE_FD_REDIR)
		close_redirection_fds(value->redirections, action & UNLINK);
}
