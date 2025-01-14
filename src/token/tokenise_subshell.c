/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_subshell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:01:54 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/11 18:25:10 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

char	*get_right_end(char *str)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = str;
	while (*tmp)
	{
		if (*tmp == '(')
			++count;
		if (*tmp == ')')
			--count;
		if (count == 0)
			break ;
		++tmp;
	}
	return (tmp);
}

int	tokenise_subshell(t_tokens *tokens, char **str, t_token_type type)
{
	char	*tmp;

	tmp = ft_substr(*str, 0, (get_right_end(*str) - (*str)) + 1);
	if (!tmp)
		return (FAILURE);
	add_token(tokens, create_token(tmp, type));
	*str += ft_strlen(tmp);
	free(tmp);
	return (SUCCESS);
}
