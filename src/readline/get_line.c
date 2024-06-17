/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:56:32 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/17 15:17:07 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char	*rl_gets(void)
{
	static char	*line_read = (char *) NULL;

	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
	line_read = readline("$> ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
