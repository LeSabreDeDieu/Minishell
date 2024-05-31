/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_factory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:09 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/31 15:21:38 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#inlude <stdbool.h>

t_env_factory	*get_env_factory(void)
{
	static t_env_factory	factory;
	if (!factory.instanced)
	{
		factory.instanced = 1;
		factory.config.sepparator = ft_strdup("=");
	}
	return (&factory);
}

boo

t_parsing_env_config	*get_env_config(void)
{
	return (&get_env_factory()->config);
}

t_env	*get_env(char *name)
{
	t_env	*current;

	current = get_env_factory()->env;
	if (!current)
		return (NULL);
	while ((ft_strncmp(current->name, name, ft_strlen(current->name)) != 0 || ft_strncmp(current->name, name, ft_strlen(name)) != 0)
		&& current->next)
		current = current->next;
	return current;
}

// void	set_env(char *name, char *value)
// {

// }


void	add_env(t_env *env)
{
	t_env_factory	*factory;
	t_env			*current;

	factory = get_env_factory();
	if (!factory->env)
	{
		factory->env = env;
		return ;
	}
	current = factory->env;
	while (current->next)
		current = current->next;
	current->next = env;
}
