/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:22:49 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/21 14:56:48 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

const char	*find_operators(const char *input)
{
	int	len;
	int	i;

	len = ft_strlen(input);
	i = 0;
	while (i < len)
	{
		if (input[i] == '&' && input[i + 1] == '&')
		{
			if (!is_in_quotes(input, i, 1) && !is_in_subshell(input, i))
				return (&input[i]);
			i++;
		}
		else if (input[i] == '|' && input[i + 1] == '|')
		{
			if (!is_in_quotes(input, i, 1) && !is_in_subshell(input, i))
				return (&input[i]);
			i++;
		}
		i++;
	}
	return (NULL);
}

bool	contain_and_or(char *str)
{
	return (find_operators(str) != NULL);
}

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
		return (error_message("quote not closed"), FAILURE);
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
