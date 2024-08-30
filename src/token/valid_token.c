/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:34:59 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/30 10:51:10 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokens.h"

static bool	is_and_or_pipe(t_token *tokens)
{
	return (tokens->type == TOKEN_AND || tokens->type == TOKEN_OR
		|| tokens->type == TOKEN_PIPE);
}

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

bool	check_quotes(t_token_list *current, t_tokens *tokens)
{
	if (current->token->type == TOKEN_DOUBLE_QUOTE
		&& counter_char_token(current->token->value, '"') % 2 != 0)
		return (free_token(tokens), false);
	if (current->token->type == TOKEN_SIMPLE_QUOTE
		&& counter_char_token(current->token->value, '\'') % 2 != 0)
		return (free_token(tokens), false);
	return (true);
}

bool	check_valid_token(t_tokens *tokens)
{
	t_token_list	*current;

	if (!tokens || !tokens->first_token)
		return (free_token(tokens), false);
	current = tokens->first_token;
	if (is_and_or_pipe(current->token) || (ft_strlen(current->token->value) == 1
			&& (current->token->value[0] == '('
				|| current->token->value[0] == ')')))
		return (free_token(tokens), false);
	while (current)
	{
		if (!check_quotes(current, tokens))
			return (false);
		if (current->token->type == TOKEN_SUBSHELL
			&& counter_char_token(current->token->value,
				'(') != counter_char_token(current->token->value, ')'))
			return (free_token(tokens), false);
		if (current->token->type == TOKEN_REDIRECTION && current->next->next
			&& current->next->next->token->type == TOKEN_SUBSHELL)
			return (free_token(tokens), false);
		if (is_and_or_pipe(current->token) && current->next == NULL)
			return (free_token(tokens), false);
		current = current->next;
	}
	return (true);
}
