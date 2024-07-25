/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:34:59 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/25 18:26:06 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"

static int	counter_char_token(char *str, char token)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == token)
			++counter;
		++i;
	}
	return (counter);
}

bool	check_valid_token(t_tokens *tokens)
{
	t_token_list	*current;

	if (!tokens || !tokens->first_token)
		return (free_token(tokens), false);
	current = tokens->first_token;
	if (current->token->type == TOKEN_AND
		|| current->token->type == TOKEN_OR
		|| current->token->type == TOKEN_PIPE)
		return (free_token(tokens), false);
	while (current)
	{
		if (ft_strlen(current->token->value) == 1
			&& (current->token->value[0] == '('
				|| current->token->value[0] == ')'))
			return (free_token(tokens), false);
		if (current->token->type == TOKEN_DOUBLE_QUOTE
			&& counter_char_token(current->token->value, '"') % 2 != 0)
			return (free_token(tokens), false);
		if (current->token->type == TOKEN_SIMPLE_QUOTE
			&& counter_char_token(current->token->value, '\'') % 2 != 0)
			return (free_token(tokens), false);
		if (current->token->type == TOKEN_SUBSHELL
			&& counter_char_token(current->token->value,
				'(') % 2 != counter_char_token(current->token->value, ')'))
			return (free_token(tokens), false);
		if (current->token->type == TOKEN_REDIRECTION && current->next->next
			&& current->next->next->token->type == TOKEN_SUBSHELL)
			return (free_token(tokens), false);
		current = current->next;
	}
	return (true);
}
