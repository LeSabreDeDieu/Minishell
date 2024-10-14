/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_all_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:44:38 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/14 11:19:04 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	open_redirection_file(t_redirection *redirection)
{
	if ((int)redirection->flag == WRITE)
		redirection->fd = open(redirection->filename,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if ((int)redirection->flag == READ
		|| (int)redirection->flag == HERE_DOC)
	{
		redirection->fd = open(redirection->filename, O_RDONLY, 0644);
	}
	else if ((int)redirection->flag == APPEND)
		redirection->fd = open(redirection->filename,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redirection->fd == -1)
	{
		error_message_command_with_arg("open", redirection->filename,
			strerror(errno));
		return (-1);
	}
	return (0);
}

int	open_all_redirection(t_redirection_list *list)
{
	t_redirection_list	*current;
	int					status;

	status = 0;
	current = list;
	while (current)
	{
		if (current->redirection.filename != NULL)
		{
			if (open_redirection_file(&(current->redirection)) == -1)
			{
				status = -1;
				break ;
			}
		}
		current = current->next;
	}
	printf("stop open status %d\n", status);
	return (status);
}
