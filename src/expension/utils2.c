/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:07:10 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/04 15:50:38 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

bool	char_in_quote(char *str, char c)
{
	if (ft_strchr(str, '"') == NULL && ft_strchr(str, '\'') == NULL)
		return (0);
	else if (ft_strchr(str, '"') != NULL)
		return ((ft_strchr(str, '"') < ft_strchr(str, c) && ft_strchr(str,
					c) < ft_strchr(ft_strchr(str, '"') + 1, '"')));
	else
		return ((ft_strchr(str, '\'') < ft_strchr(str, c) && ft_strchr(str,
					c) < ft_strchr(ft_strchr(str, '\'') + 1, '\'')));
}

void	dequote_delimiter(t_redirection_list *redir_list)
{
	t_redirection_list	*current;
	char				*filename;

	current = redir_list;
	while (current)
	{
		if (current->redirection.flag == HERE_DOC)
		{
			filename = dequote(current->redirection.filename);
			current->redirection.filename = filename;
		}
		current = current->next;
	}
}
