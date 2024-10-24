/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:55:05 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/18 15:03:56 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	len_env(void)
{
	t_env	*current;
	size_t	len;

	current = get_env_factory()->env;
	len = 0;
	while (current)
	{
		++len;
		current = current->next;
	}
	return (len);
}

size_t	len_array(char **array)
{
	char	**move;

	move = array;
	while (*move)
		++move;
	return (move - array);
}
