/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:45:46 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/03 13:07:58 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	close_std_fds(t_ast_value *value)
{
	if (value->fd_in != -1)
		close(value->fd_in);
	if (value->fd_out != -1)
		close(value->fd_out);
	value->fd_out = -1;
	value->fd_in = -1;
}

void	close_pipe_fds(t_ast_value *value)
{
	if (value->fd_out != -1)
	{
		close(value->fd_out);
		value->fd_out = -1;
	}
}

void	close_redirection_fds(t_redirection_list *list)
{
	t_redirection_list	*current;

	current = list;
	while (current)
	{
		if (current->redirection.filename != NULL
			&& current->redirection.fd != -1)
		{
			close(current->redirection.fd);
			if (current->redirection.flag == HERE_DOC)
				unlink(current->redirection.filename);
		}
		current->redirection.fd = -1;
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
		close_redirection_fds(value->redirections);
}
