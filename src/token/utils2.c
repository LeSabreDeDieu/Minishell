/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:51:41 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/16 13:57:43 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

bool	is_space_in_quotes(char *str)
{
	int		quote;
	int		i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = !quote;
		if (str[i] == ' ' && quote)
			return (1);
		++i;
	}
	return (0);
}