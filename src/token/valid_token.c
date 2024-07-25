/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:34:59 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/10 15:44:58 by sgabsi           ###   ########.fr       */
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

	current = tokens->first_token;
	while (current)
	{
		if (ft_strlen(current->token->value) == 1
			&& (current->token->value[0] == '('
				|| current->token->value[0] == ')'))
			return (false);
		if (current->token->type == TOKEN_DOUBLE_QUOTE
			&& counter_char_token(current->token->value, '"') % 2 != 0)
			return (false);
		if (current->token->type == TOKEN_SIMPLE_QUOTE
			&& counter_char_token(current->token->value, '\'') % 2 != 0)
			return (false);
		if (current->token->type == TOKEN_SUBSHELL
			&& counter_char_token(current->token->value,
				'(') % 2 != counter_char_token(current->token->value, ')'))
			return (false);
		if (current->token->type == TOKEN_REDIRECTION && current->next->next
			&& current->next->next->token->type == TOKEN_SUBSHELL)
			return (false);
		current = current->next;
	}
	return (true);
}
