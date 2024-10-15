/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:22:49 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/15 16:18:49 by gcaptari         ###   ########.fr       */
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
			if (!is_in_quotes(input, i) && !is_in_subshell(input, i))
				return (&input[i]);
			i++;
		}
		else if (input[i] == '|' && input[i + 1] == '|')
		{
			if (!is_in_quotes(input, i) && !is_in_subshell(input, i))
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

static size_t	get_len_word(char *str)
{
	size_t	size;
	char	quote;

	size = 0;
	while (str[size])
	{
		if (str[size] == '<' || str[size] == '>' || str[size] == '|'
			|| str[size] == ' ' || str[size] == '(' || str[size] == '\n'
			|| ft_strncmp(&str[size], "&&", 2) == 0)
			break ;
		else if (str[size] == '\'' || str[size] == '\"')
		{
			quote = str[size];
			++size;
			while (str[size] && str[size] != quote)
				++size;
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
	tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	ft_memmove(tmp, *str, len);
	*str += len;
	return (tmp);
}
