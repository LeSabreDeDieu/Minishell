/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:34:59 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/10 15:43:45 by sgabsi           ###   ########.fr       */
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
	char	*value;
	char	type_quote;
	char	is_quoted;

	value = current->token->value;
	while (*value)
	{
		if (*value == tokens->token_config[current->token->type][0]
			&& is_quoted == 0 && *value != type_quote)
		{
			type_quote = tokens->token_config[current->token->type][0];
			is_quoted = 1;
		}
	}
	return (true);
}

bool	check_valid_token(t_tokens *tokens)
{
	t_token_list	*current;

	if (!tokens || !tokens->first_token)
		return (free_token(tokens), false);
	current = tokens->first_token;
	if (is_and_or_pipe(current->token))
		return (free_token(tokens), false);
	while (current)
	{
		if (current->token->type == TOKEN_REDIRECTION && current->next == NULL)
			return (free_token(tokens), false);
		if ((ft_strlen(current->token->value) == 1
				&& (current->token->value[0] == '('
					|| current->token->value[0] == ')')))
			return (free_token(tokens), false);
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
