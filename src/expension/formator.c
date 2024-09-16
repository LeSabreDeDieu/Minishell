/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:16:19 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/16 13:09:52 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

void	expend_variable(t_ast_value *value, int i, int *j, bool is_quoted)
{
	char	pid_str[16];

	if (value->argv[i][(*j)] == '\'' && !is_quoted)
		(*j) += pos_next_quote(&value->argv[i][(*j) + 1]) + 1;
	if (value->argv[i][(*j)] == '$' && value->argv[i][(*j) + 1] == '$')
	{
		ft_bzero(pid_str, sizeof(char *));
		get_pid_as_string(pid_str);
		value->argv[i] = ft_str_replace(value->argv[i], "$$", pid_str);
	}
	if (value->argv[i][(*j)] == '$' && value->argv[i][(*j) + 1] != '$')
		expend_variable_from_env(value, i, j);
}

int	expend(t_ast_value *value)
{
	int		i;
	int		j;
	bool	is_quoted;

	if (!value || !value->argv || !value->argc)
		return (FAILURE);
	i = 0;
	is_quoted = false;
	while (value->argv[i] && i < value->argc)
	{
		j = 0;
		while (value->argv[i][j])
		{
			is_quoted = is_in_dquote(value->argv[i][j], is_quoted);
			expend_variable(value, i, &j, is_quoted);
			if (value->argv[i][j] == '*')
			{
				if (expand_wildcard(value->argv[i], &value->argv,
						&value->argc) == FAILURE)
					return (FAILURE);
				else
				{
					i = (value->argc - 1);
					break ;
				}
			}
			++j;
		}
		++i;
	}
	value->name = value->argv[0];
	return (SUCCESS);
}
