/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:55:39 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/05 14:26:54 by sgabsi           ###   ########.fr       */
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
			|| str[size] == '$' || str[size] == '\n'
			|| ft_strncmp(&str[size], "&&", 2) == 0 || str[size] == ' ')
			break ;
		++size;
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
	ft_memmove(tmp, *str, len);
	*str += len - 1;
	return (tmp);
}
