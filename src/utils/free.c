/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:48:08 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/23 13:42:59 by gcaptari         ###   ########.fr       */
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

void	free_token(t_tokens *tokens)
{
	t_token_list	*tmp;
	t_token_list	*current;

	if (!tokens || !tokens->first_token)
		return ;
	current = tokens->first_token;
	while (current)
	{
		tmp = current;
		current = tmp->next;
		if (tmp->token)
		{
			if (tmp->token->value)
				free(tmp->token->value);
			free(tmp->token);
		}
		free(tmp);
	}
	tokens->first_token = NULL;
}

void	free_minishell(t_minishell *minishell, int action)
{
	if (action & FREE_AST)
		free_ast(&minishell->ast);
	if ((action & FREE_TOKEN) && minishell->tokens)
	{
		free_token(minishell->tokens);
		free(minishell->tokens);
	}
	if (action & FREE_ENV)
		free_env();
	if (action & FREE_UNAME)
		free(minishell->data.username);
}
