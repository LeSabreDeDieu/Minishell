/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:07:10 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/17 15:24:31 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

bool	char_in_quote(char *str, char c)
{
	if (ft_strchr(str, '"') == NULL && ft_strchr(str, '\'') == NULL)
		return (0);
	else if (ft_strchr(str, '"') != NULL)
		return ((ft_strchr(str, '"') < ft_strchr(str, c) && ft_strchr(str,
					c) < ft_strchr(ft_strchr(str, '"') + 1, '"')));
	else
		return ((ft_strchr(str, '\'') < ft_strchr(str, c) && ft_strchr(str,
					c) < ft_strchr(ft_strchr(str, '\'') + 1, '\'')));
}

const char	*find_space(const char *input)
{
	int	len;
	int	i;

	len = ft_strlen(input);
	i = 0;
	while (i < len)
	{
		if (ft_isspace(input[i]))
		{
			if (!is_in_quotes(input, i, -1) && !is_in_subshell(input, i))
				return (&input[i]);
		}
		i++;
	}
	return (NULL);
}

void	dequote_delimiter(t_redirection_list *redir_list)
{
	t_redirection_list	*current;
	char				*filename;

	current = redir_list;
	while (current)
	{
		if (current->redirection.flag == HERE_DOC)
		{
			filename = dequote(current->redirection.filename);
			current->redirection.filename = filename;
		}
		current = current->next;
	}
}

bool	is_dollar_allone(t_ast_value *value, t_pos *pos)
{
	return (value->argv[(*pos).i][(*pos).j] == '$'
			&& (ft_isspace(value->argv[(*pos).i][(*pos).j + 1])
				|| !value->argv[(*pos).i][(*pos).j + 1]));
}
