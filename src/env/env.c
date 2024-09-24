/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:20:04 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/23 14:51:46 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "stdio.h"

t_env	*new_env(char *name, char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(*env));
	if (!env || !name || !value)
		return (free(env), NULL);
	env->name = ft_strdup(name);
	if (!env->name)
		return (free(env), NULL);
	env->value = ft_strdup(value);
	if (!env->value)
		return (free(env->name), free(env), NULL);
	return (env);
}

void	create_env(char *envp[])
{
	char			**move;
	t_parsing_env	parsing_env;
	t_env			*new;

	if (!envp)
	{
		return ;
	}
	move = envp;
	while (*move)
	{
		parsing_env = parser_env(*move++);
		if (!parsing_env.name || !parsing_env.value)
			continue ;
		new = new_env(parsing_env.name, parsing_env.value);
		if (!new)
		{
			free(parsing_env.name);
			free(parsing_env.value);
			continue ;
		}
		free(parsing_env.name);
		free(parsing_env.value);
		add_env((t_env *)new);
	}
}

void	print_env(void)
{
	t_env_factory	*factory;
	t_env			*current;

	factory = get_env_factory();
	current = factory->env;
	if (!current)
		return ;
	while (current)
	{
		ft_putstr_fd(current->name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(current->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
}
