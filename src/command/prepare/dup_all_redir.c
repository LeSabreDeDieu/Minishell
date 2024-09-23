/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_all_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:45:14 by gcaptari          #+#    #+#             */
/*   Updated: 2024/09/23 12:05:16 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	dup_redirection(t_redirection *redirection)
{
	if (redirection->fd == -1)
		return (-1);
	if ((int)redirection->flag == WRITE || (int)redirection->flag == APPEND)
	{
		dup2(redirection->fd, STDOUT_FILENO);
	}
	else if ((int)redirection->flag == READ || (int)redirection->flag == HERE_DOC)
	{
		dup2(redirection->fd, STDIN_FILENO);
	}
	close(redirection->fd);
	return (0);
}

int	dup_all_redir(t_redirection_list *list)
{
	t_redirection_list	*current;
	int					status;

	current = list;
	status = 0;
	while (current)
	{
		if (current->redirection.filename != NULL)
		{
			if (dup_redirection(&(current->redirection)) == -1)
			{
				status = -1;
				break ;
			}
		}
		current = current->next;
	}
	return (status);
}
