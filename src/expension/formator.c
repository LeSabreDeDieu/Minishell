/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:16:19 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/23 16:52:13 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

static void	expend_variable(t_minishell *shell_data, t_ast_value *value,
		t_pos *pos, bool is_quoted)
{
	char	pid_str[16];

	if (value->argv[pos->i][pos->j] == '\'' && !is_quoted)
		pos->j += pos_next_quote(&value->argv[pos->i][pos->j + 1]) + 1;
	if (value->argv[pos->i][pos->j] == '$' && value->argv[pos->i][pos->j
		+ 1] == '?')
	{
		value->argv[pos->i] = ft_str_replace(value->argv[pos->i], "$?",
				ft_itoa(shell_data->current_status));
		++pos->j;
	}
	if (value->argv[pos->i][pos->j] == '$' && value->argv[pos->i][pos->j
		+ 1] == '$')
	{
		ft_bzero(pid_str, sizeof(char *));
		get_pid_as_string(pid_str);
		value->argv[pos->i] = ft_str_replace(value->argv[pos->i], "$$",
				pid_str);
	}
	if (value->argv[pos->i][pos->j] == '$' && value->argv[pos->i][pos->j
		+ 1] != '$')
		expend_variable_from_env(value, pos->i, &pos->j);
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

static int	expend_special_char(t_minishell *shell_data, t_ast_value *value,
		t_pos *pos)
{
	if (value->argv[(*pos).i] && ft_strchr(value->argv[(*pos).i], '*') != NULL)
	{
		if (expend_wildcard(&value->argv, &value->argc) == FAILURE)
			return (FAILURE);
	}
	else if (value->argv[(*pos).i][(*pos).j] == '~'
		&& value->argv[(*pos).i][(*pos).j + 1] == '/')
		value->argv[(*pos).i] = expend_tild(shell_data, value, (*pos).i);
	else if (value->argv[(*pos).i][(*pos).j] == '~'
		&& value->argv[(*pos).i][(*pos).j + 1] == '\0')
		value->argv[(*pos).i] = expend_tild(shell_data, value, (*pos).i);
	return (SUCCESS);
}

static int	expend2(t_minishell *shell_data, t_ast_value *value, t_pos *pos,
		bool is_quoted)
{
	int	ret;

	while (value->argv[(*pos).i][(*pos).j])
	{
		is_quoted = is_in_dquote(value->argv[(*pos).i][(*pos).j], is_quoted);
		if (value->argv[(*pos).i][(*pos).j] == '$'
			&& (ft_isspace(value->argv[(*pos).i][(*pos).j + 1])
				|| !value->argv[(*pos).i][(*pos).j + 1]))
			continue ;
		expend_variable(shell_data, value, pos, is_quoted);
		ret = expend_special_char(shell_data, value, pos);
		if (ret == FAILURE)
			return (FAILURE);
		++(*pos).j;
	}
	return (SUCCESS);
}

int	expend(t_minishell *shell_data, t_ast_value *value)
{
	t_pos	pos;
	bool	is_quoted;

	if (!value || !value->argv || !value->argc)
		return (FAILURE);
	pos.i = -1;
	is_quoted = false;
	while (value->argv[++pos.i] && pos.i < value->argc)
	{
		pos.j = 0;
		expend2(shell_data, value, &pos, is_quoted);
	}
	value->name = value->argv[0];
	return (SUCCESS);
}
