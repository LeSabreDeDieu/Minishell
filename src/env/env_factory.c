/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_factory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:09 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/05 16:34:56 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdbool.h>
#include <stdio.h>

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
	while ((ft_strncmp(current->name, name, ft_strlen(current->name)) != 0
			|| ft_strncmp(current->name, name, ft_strlen(name)) != 0)
		&& current->next)
		current = current->next;
	if ((ft_strncmp(current->name, name, ft_strlen(current->name)) != 0
			|| ft_strncmp(current->name, name, ft_strlen(name)) != 0))
		return (NULL);
	return (current);
}

void	add_env(t_env *env)
{
	t_env_factory	*factory;
	t_env			*current;

	factory = get_env_factory();
	if (env)
		factory->length++;
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

void	unset_env(char *name)
{
	t_env	*current;
	t_env	*find;

	find = get_env(name);
	if (!find)
		return ;
	current = get_env_factory()->env;
	get_env_factory()->length--;
	while (current)
	{
		if (current == find)
		{
			get_env_factory()->env = find->next;
			break ;
		}
		else if (current->next == find)
		{
			current->next = find->next;
			break ;
		}
		current = current->next;
	}
	free(find->name);
	free(find->value);
	free(find);
}


void	set_env(char *name, char *value)
{
	t_env	*current;
	char	*tmp;

	current = get_env(name);
	if (current)
	{
		tmp = current->value;
		current->value = ft_strdup(value);
		if (!current->value)
			current->value = tmp;
		else
			free(tmp);
		return ;
	}
	add_env(new_env(name, value));
}
