/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:20:04 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/31 15:16:23 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *name, char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(*env));
	if (!env || !name || !value)
		return (NULL);
	env->name = ft_strdup(name);
	env->value = ft_strdup(value);
	return (env);
}

void	create_env(char *envp[])
{
	char	**move;

	if (!envp)
		return ;
	move = envp;
	while (*move)
	{
		const t_parsing_env parsing_env = parser_env(*move++);
		if (!parsing_env.name || !parsing_env.value)
			continue;
		const t_env *new = new_env(parsing_env.name, parsing_env.value);
		if (!new)
		{
			free(parsing_env.name);
			free(parsing_env.value);
			continue;
		}
		free(parsing_env.name);
		free(parsing_env.value);
		add_env((t_env * )new);
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
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}


