/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:51:41 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/23 13:50:53 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int	is_in_quotes(const char *str, int index, int mult)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (i < index)
	{
		if (str[i] == ('\'' * mult))
			single_quote = !single_quote;
		else if (str[i] == ('"' * mult))
			double_quote = !double_quote;
		i++;
	}
	return (single_quote || double_quote);
}

int	is_in_subshell(const char *str, int index)
{
	int	subshell_count;
	int	i;

	subshell_count = 0;
	i = 0;
	while (i < index)
	{
		if (str[i] == '(')
			subshell_count++;
		else if (str[i] == ')')
			subshell_count--;
		i++;
	}
	return (subshell_count > 0);
}

bool	is_space_in_quotes(char *str)
{
	int	quote;
	int	i;

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
