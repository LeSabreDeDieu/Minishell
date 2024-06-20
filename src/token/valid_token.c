/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:54:50 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/18 15:44:35 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int	counter_char_token(char *str, char token)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == token)
			counter++;
		i++;
	}
	return (counter);
}

bool	check_valid_token(void)
{
	t_token_factory	*t_fac;
	t_token_list	*current;

	t_fac = get_token_factory();
	current = t_fac->token_list;
	while (current)
	{
		if (current->token->type == TOKEN_DOUBLE_QUOTE
			&& counter_char_token(current->token->value, '"') % 2 != 0)
			return (false);
		if (current->token->type == TOKEN_SIMPLE_QUOTE
			&& counter_char_token(current->token->value, '\'') % 2 != 0)
			return (false);
		if (current->token->type == TOKEN_SUBSHELL
			&& counter_char_token(current->token->value,
				'(') != counter_char_token(current->token->value, ')'))
			return (false);
		current = current->next;
	}
	return (true);
}
