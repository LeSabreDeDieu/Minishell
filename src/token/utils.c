/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:55:39 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/13 10:09:47 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokens.h"
#include <stdio.h>

static size_t	get_len_word(char *str)
{
	size_t	size;

	size = 0;
	while (str[size])
	{
		if (str[size] == '<' || str[size] == '>' || str[size] == '|'
			|| str[size] == '"' || str[size] == '\'' || str[size] == '('
			|| str[size] == ')' || str[size] == '$')
			break ;
		size++;
	}
	return (size);
}

char	*get_word(char **str)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	if (!str || !*str || !**str)
		return (NULL);
	len = get_len_word(*str);
	tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = -1;
	while (++i < len)
		tmp[i] = (*str)[i];
	*str += len;
	return (tmp);
}
