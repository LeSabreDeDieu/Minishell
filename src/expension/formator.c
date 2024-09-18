/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:16:19 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/17 14:55:39 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

static void	expend_variable(t_minishell *shell_data, t_ast_value *value, int i, int *j, bool is_quoted)
{
	char	pid_str[16];

	if (value->argv[i][(*j)] == '\'' && !is_quoted)
		(*j) += pos_next_quote(&value->argv[i][(*j) + 1]) + 1;
	if (value->argv[i][(*j)] == '$' && !value->argv[i][(*j) + 1])
		++(*j);
	if (value->argv[i][(*j)] == '$' && value->argv[i][(*j) + 1] == '?')
	{
		value->argv[i] = ft_str_replace(value->argv[i], "$?", ft_itoa(shell_data->current_status));
		++(*j);
	}
	if (value->argv[i][(*j)] == '$' && value->argv[i][(*j) + 1] == '$')
	{
		ft_bzero(pid_str, sizeof(char *));
		get_pid_as_string(pid_str);
		value->argv[i] = ft_str_replace(value->argv[i], "$$", pid_str);
	}
	if (value->argv[i][(*j)] == '$' && value->argv[i][(*j) + 1] != '$')
		expend_variable_from_env(value, i, j);
}

static char	*expend_tild(t_minishell *shell_data, t_ast_value *value, int i)
{
	char	*tmp;
	char	*home;

	tmp = ft_strjoin("/home/", shell_data->data.username);
	home = ft_str_replace(value->argv[i], "~", tmp);
	free(tmp);
	return (home);
}

static int	expend_special_char(t_minishell *shell_data, t_ast_value *value, int i, int j)
{
	if (value->argv[i][j] == '*')
	{
		if (expand_wildcard(value->argv[i], &value->argv,
				&value->argc) == FAILURE)
			return (FAILURE);
		else
		{
			i = (value->argc - 1);
			return (1);
		}
	}
	else if (value->argv[i][j] == '~' && value->argv[i][j + 1] == '/')
		value->argv[i] = expend_tild(shell_data, value, i);
	else if (value->argv[i][j] == '~' && value->argv[i][j + 1] == '\0')
		value->argv[i] = expend_tild(shell_data, value, i);
	return (SUCCESS);
}

int	expend(t_minishell *shell_data, t_ast_value *value)
{
	int		i;
	int		j;
	bool	is_quoted;
	int 	ret;

	if (!value || !value->argv || !value->argc)
		return (FAILURE);
	i = -1;
	is_quoted = false;
	while (value->argv[++i] && i < value->argc)
	{
		j = -1;
		while (value->argv[i][++j])
		{
			is_quoted = is_in_dquote(value->argv[i][j], is_quoted);
			expend_variable(shell_data, value, i, &j, is_quoted);
			ret = expend_special_char(shell_data, value, i, j);
			if (ret == FAILURE)
				return (FAILURE);
			if (ret != SUCCESS)
				break ;
		}
	}
	value->name = value->argv[0];
	return (SUCCESS);
}
