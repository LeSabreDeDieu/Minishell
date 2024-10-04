/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:40:26 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/04 16:53:21 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

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

int	add_token(t_tokens *tokens, t_token *token)
{
	t_token_list	*current;
	t_token_list	*new_token;

	if (!token)
		return (FAILURE);
	if (!tokens->first_token)
	{
		new_token = ft_calloc(1, sizeof(t_token_list));
		if (!new_token)
			return (FAILURE);
		new_token->token = token;
		tokens->first_token = new_token;
		return (SUCCESS);
	}
	current = tokens->first_token;
	while (current->next)
		current = current->next;
	current->next = ft_calloc(1, sizeof(*current->next));
	if (!current->next)
		return (FAILURE);
	current->next->token = token;
	current->next->prev = current;
	return (SUCCESS);
}
