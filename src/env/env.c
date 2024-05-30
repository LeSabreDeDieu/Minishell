/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:20:04 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/30 16:06:33 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *name, char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(*env));
	if (!env)
		return (NULL);
	env->name = name;
	env->value = value;
	return (env);
}

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

void	create_env(char *envp[])
{
	char	**split;
	char	**move;
	char	*tmp;
	char	*line;

	if (!envp || !*envp)
		return ;
	split = ft_split(*envp, '=');
	if (!split)
		return ;
	line = NULL;
	move = split + 1;
	while (*move)
	{
		tmp = ft_strjoin_gnl(line, *move);
		if (!tmp)
		{
			free_str_tab(split);
			free(line);
			return ;
		}
		line = ft_strjoin_gnl(tmp, "=");
		if (!line)
		{
			free_str_tab(split);
			return ;
		}
		free(*move++);
	}
	tmp = line;
	line = ft_strtrim(tmp, "=");
	free(tmp);
	if (!line)
	{
		free_str_tab(split);
		return ;
	}
	add_env(new_env(split[0], line));
	(free(split), create_env(++envp));
}

void	print_env(void)
{
	t_env_factory	*factory;
	t_env			*current;

	factory = get_env_factory();
	current = factory->env;
	if (!current)
		return ;
	while (current->next)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

void	free_env(void)
{
	t_env_factory	*factory;
	t_env			*tmp;
	t_env			*current;

	factory = get_env_factory();
	current = factory->env;
	if (!current)
		return ;
	while (current)
	{
		tmp = current;
		current = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}
