/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:03:21 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/18 15:39:49 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"

static void	create_token_config(t_token_factory *fac)
{
	t_token_config	*config;

	config = &fac->config;
	config->and = "&&";
	config->or = "||";
	config->redirection = "<>";
	config->pipe = '|';
	config->variable = '$';
	config->subshell_start = '(';
	config->subshell_end = ')';
	config->double_quote = '\"';
	config->simple_quote = '\'';
}

t_token_factory	*get_token_factory(void)
{
	static t_token_factory	factory;

	if (!factory.instanced)
	{
		factory.instanced = true;
		create_token_config(&factory);
	}
	return (&factory);
}

t_token_config	*get_token_config(void)
{
	return (&get_token_factory()->config);
}

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (!token || !value)
		return (free(token), NULL);
	token->value = ft_strdup(value);
	if (!token->value)
		return (free(token), NULL);
	token->type = type;
	return (token);
}

void	add_token(t_token *token)
{
	t_token_factory	*fac;
	t_token_list	*current;

	if (!token)
		return ;
	fac = get_token_factory();
	if (!fac->token_list)
	{
		fac->token_list = ft_calloc(1, sizeof(*fac->token_list));
		fac->token_list->token = token;
		return ;
	}
	current = fac->token_list;
	while (current->next)
		current = current->next;
	current->next = ft_calloc(1, sizeof(*current->next));
	current->next->token = token;
}
