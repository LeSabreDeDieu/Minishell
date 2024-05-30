/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_factory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:09 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/30 15:44:11 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_factory	*get_env_factory(void)
{
	static t_env_factory	env;

	return (&env);
}

t_env	get_env(char *name)
{
	t_env	*current;

	current = get_env_factory()->env;
	if (!current)
		return ((t_env){.name = NULL, .value = NULL, .next = NULL});
	while (ft_strncmp(current->name, name, ft_strlen(current->name)) != 0
		&& current->next)
		current = current->next;
	return ((t_env){.name = current->name, .value = current->value,
		.next = NULL});
}
