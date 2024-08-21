/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:16:19 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/21 08:19:40 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rl_gets(void)
{
	char	*line;

	line = readline("$> ");
	if (!line)
		return (NULL);
	if (*line)
		add_history(line);
	return (line);
}
