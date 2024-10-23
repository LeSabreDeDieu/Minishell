/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:24:32 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/23 13:54:25 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"
#include <unistd.h>

bool	is_in_dquote(char *c, bool is_quoted)
{
	if (*c == (char)('"' * -1))
		return (!is_quoted);
	return (is_quoted);
}

bool	is_dollar_allone(t_ast_value *value, t_pos *pos)
{
	return (value->argv[(*pos).i][(*pos).j] == '$'
			&& (ft_isspace(value->argv[(*pos).i][(*pos).j + 1])
				|| !value->argv[(*pos).i][(*pos).j + 1]));
}

int	expend_variable_from_env(t_ast_value *value, int *i, int j, bool is_quoted)
{
	char	*to_exp;
	t_env	*env;
	char	*env_value;

	env_value = "";
	(void) is_quoted;
	to_exp = ft_substr(value->argv[(*i)], j, ft_strlen(&value->argv[(*i)][(j)])
			- ft_strlen(get_end(value->argv[(*i)] + ((j) + 1))));
	if (to_exp == NULL)
		return (FAILURE);
	env = get_env(to_exp + 1);
	if (env != NULL)
		env_value = env->value;
	value->argv[(*i)] = ft_str_replace(value->argv[(*i)], to_exp, env_value);
	free(to_exp);
	return (SUCCESS);
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
