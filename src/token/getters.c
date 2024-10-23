/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:22:49 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/23 14:24:49 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

static int	get_len_quote(char *str, size_t *size)
{
	char	quote;
	char	evode;

	quote = str[(*size)];
	if (quote == '\'')
		evode = '\'';
	else
		evode = '\"';
	if (is_quote_closed(&str[(*size)], quote, evode) == false)
		return (error_message("quote not closed"), ENOENT);
	++(*size);
	while (str[(*size)] && str[(*size)] != quote)
		++(*size);
	if (!str[(*size)])
		return (LOOP_END);
	return (SUCCESS);
}

static size_t	get_len_word(char *str)
{
	size_t	size;
	int		rep;

	size = 0;
	while (str[size])
	{
		if (str[size] == '<' || str[size] == '>' || str[size] == '|'
			|| str[size] == ' ' || str[size] == '(' || str[size] == '\n'
			|| ft_strncmp(&str[size], "&&", 2) == 0)
			break ;
		else if (str[size] == '\'' || str[size] == '\"')
		{
			rep = get_len_quote(str, &size);
			if (rep == FAILURE)
				return ((size_t)(-1));
			else if (rep == ENOENT)
				return (errno = ENOENT, (size_t)(-1));
			else if (rep == LOOP_END)
				break ;
		}
		++size;
	}
	return (size);
}

char	*get_word(char **str)
{
	char	*tmp;
	size_t	len;

	if (!str || !*str || !**str)
		return (NULL);
	len = get_len_word(*str);
	if (len == (size_t)-1)
		return (NULL);
	tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	ft_memmove(tmp, *str, len);
	*str += len;
	return (tmp);
}
