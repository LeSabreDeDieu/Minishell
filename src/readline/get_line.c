/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:56:32 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/13 18:10:44 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_line(void)
{
	static char	*line_read = (char *) NULL;

	return (&line_read);
}

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char	*rl_gets(void)
{
	char	**line_read;

	line_read = get_line();
	if (*line_read)
	{
		free(*line_read);
		*line_read = (char *) NULL;
	}
	*line_read = readline("$> ");
	if (*line_read && **line_read)
		add_history(*line_read);
	return (*line_read);
}
