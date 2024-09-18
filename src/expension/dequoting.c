/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequoting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:40:30 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/18 15:42:41 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

char	*sub_str_in_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = str[i++];
	while (str[i])
	{
		if (str[i] == quote)
			break ;
		++i;
	}
	return (ft_substr(str, 1, i - 1));
}

void	dequote_quote(char *str, int *i, char **result, char **new_result)
{
	char	*temp;

	if (!(*result))
		(*new_result) = ft_substr(str, 0, (*i));
	else
	{
		(*new_result) = ft_strdup((*result));
		free((*result));
	}
	temp = sub_str_in_quote(&str[(*i)]);
	if (new_result)
		(*result) = ft_strjoin((*new_result), temp);
	else
		(*result) = ft_strdup(temp);
	(*i) += ft_strlen(temp) + 2;
	free(temp);
	free((*new_result));
}

void	dequote_none_quote(char *str, int *i, char **result, char **new_result)
{
	char	*temp;

	temp = ft_strndup(&str[(*i)], 1);
	if ((*result))
		(*new_result) = ft_strjoin((*result), temp);
	else
		(*new_result) = ft_strdup(temp);
	free(temp);
	free((*result));
	(*result) = ft_strdup((*new_result));
	free((*new_result));
	++(*i);
}

char	*dequote(char *str)
{
	char	*result;
	char	*new_result;
	int		i;

	i = 0;
	result = NULL;
	new_result = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			dequote_quote(str, &i, &result, &new_result);
		else
			dequote_none_quote(str, &i, &result, &new_result);
	}
	free(str);
	return (result);
}

void	to_dequote(t_ast_value *value)
{
	int	i;

	if (!value || !value->argv || !value->argc)
		return ;
	i = 0;
	while (value->argv[i] && i < value->argc)
	{
		value->argv[i] = dequote(value->argv[i]);
		++i;
	}
	value->name = value->argv[0];
}
