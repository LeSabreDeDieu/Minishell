/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_value_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:21:34 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/19 16:34:22 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

bool	is_quote(t_token *token)
{
	return (token->type == TOKEN_DOUBLE_QUOTE
		|| token->type == TOKEN_SIMPLE_QUOTE);
}

int	create_redirection_list(t_ast_value **value, t_token_list **current)
{
	while ((*current) && (*current)->token->type == TOKEN_REDIRECTION)
	{
		if ((*current)->next && add_list_redirection(&(*value)->redirections,
				(*current)->token, (*current)->next->token->value) == FAILURE)
			return (FAILURE);
		(*current) = (*current)->next->next;
	}
	return (SUCCESS);
}

int	count_nb_arg(t_ast_value **value, t_token_list **current)
{
	t_token_list	*tmp;

	tmp = (*current);
	while (tmp && (tmp->token->type == TOKEN_WORD
			|| tmp->token->type == TOKEN_REDIRECTION || is_quote(tmp->token)))
	{
		while (tmp && (tmp->token->type == TOKEN_WORD || is_quote(tmp->token)))
		{
			(*value)->argc++;
			tmp = tmp->next;
		}
		while (tmp && tmp->token && tmp->token->type == TOKEN_REDIRECTION)
		{
			if (tmp->next && add_list_redirection(&(*value)->redirections,
					tmp->token, tmp->next->token->value) == FAILURE)
				return (FAILURE);
			tmp = tmp->next->next;
		}
	}
	return (SUCCESS);
}

int	add_argv_value(t_ast_value **value, t_token_list **current)
{
	int	i;

	i = 0;
	while ((*current) && ((*current)->token->type == TOKEN_WORD
			|| (*current)->token->type == TOKEN_REDIRECTION
			|| is_quote((*current)->token)))
	{
		while ((*current) && ((*current)->token->type == TOKEN_WORD
				|| is_quote((*current)->token)))
		{
			(*value)->argv[i++] = ft_strdup((*current)->token->value);
			(*current) = (*current)->next;
		}
		while ((*current) && (*current)->token
			&& (*current)->token->type == TOKEN_REDIRECTION)
		{
			if (!(*current)->next)
				return (FAILURE);
			(*current) = (*current)->next->next;
		}
	}
	return (SUCCESS);
}
