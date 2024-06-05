/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:19:27 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/30 15:55:09 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_tab(char **tabs)
{
	char	**move;

	move = tabs;
	while (*move)
		free(*move++);
	free(tabs);
}

void	free_env(void)
{
	t_env_factory	*factory;
	t_env			*tmp;
	t_env			*current;

	factory = get_env_factory();
	free(factory->config.sepparator);
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

void	free_token(void)
{
	t_token_factory	*fac;
	t_token			*tmp;
	t_token			*current;

	fac = get_token_factory();
	current = fac->token;
	if (!current)
		return ;
	while (current)
	{
		tmp = current;
		current = tmp->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
