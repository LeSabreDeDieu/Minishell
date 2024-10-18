/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:04:53 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/18 13:07:56 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	add_shlvl(void)
{
	t_env	*env;
	char	*env_value;
	int		shlvl;

	shlvl = 0;
	env = get_env("SHLVL");
	if (!env)
	{
		set_env("SHLVL", "1");
		return ;
	}
	env_value = env->value;
	shlvl = ft_atoi(env_value);
	env_value = ft_itoa(++shlvl);
	set_env("SHLVL", env_value);
	free(env_value);
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
	while (current && current->next)
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

	if (!name || !value)
		return ;
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
