/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:54:50 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/13 10:13:31 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

bool	check_valid_token(void)
{
	t_token_factory	*t_fac;
	t_token			*current;
	int				num_of_double_quote;
	int				num_of_simple_quote;		

	t_fac = get_token_factory();
	current = t_fac->token;
	// while (current->next)
	// {
	// 	if (current->type == TOKEN_DOUBLE_QUOTE)
	// 	if (current->type == TOKEN_SIMPLE_QUOTE)
	// 	if (current->type == TOKEN_SUBSHELL)
	// }
}
