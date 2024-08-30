/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:22:49 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/30 10:51:13 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "tokens.h"
#include "libft.h"

static bool	check_is_in_shell_2(char *str, char *and, char *or)
{
	char	*search;

	search = ft_strstr(str, "\'");
	if (!search)
		return (1);
	if (and && and < search)
		return (1);
	if (or && or < search)
		return (1);
	return (0);
}

bool	check_is_in_shell(char *str)
{
	char	*search;
	char	*and;
	char	*or;

	search = ft_strstr(str, "(");
	if (!search)
		return (1);
	and = ft_strstr(str, "&&");
	or = ft_strstr(str, "||");
	if (and && and < search)
		return (1);
	if (or && or < search)
		return (1);
	search = ft_strstr(str, "\"");
	if (!search)
		return (1);
	if (and && and < search)
		return (1);
	if (or && or < search)
		return (1);
	if (check_is_in_shell_2(str, and, or) == 1)
		return (1);
	return (0);
}

bool	contain_and_or(char *str)
{
	return (*str != '(' && *str != '"' && *str != '\'' && check_is_in_shell(str)
		&& (ft_strstr(str, "&&") != NULL || ft_strstr(str, "||") != NULL));
}

static size_t	get_len_word(char *str)
{
	size_t	size;

	size = 0;
	while (str[size])
	{
		if (str[size] == '<' || str[size] == '>' || str[size] == '|'
			|| str[size] == ' ' || str[size] == '('
			|| str[size] == '$' || str[size] == '\n'
			|| ft_strncmp(&str[size], "&&", 2) == 0)
			break ;
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
	*str += len - 1;
	return (tmp);
}
