/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:03:24 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/23 15:55:21 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

static int	expend_variable(t_minishell *shell_data, t_ast_value *value,
		t_pos *pos, bool is_quoted)
{
	char	pid_str[16];

	if (value->argv[pos->i][pos->j] == '$' && value->argv[pos->i][pos->j
		+ 1] == '?')
		expend_last_status(shell_data, value, pos);
	else if (value->argv[pos->i][pos->j] == '$' && value->argv[pos->i][pos->j
		+ 1] == '~')
		value->argv[pos->i] = ft_str_replace(value->argv[pos->i], "$~", "$~");
	else if (value->argv[pos->i][pos->j] == '$' && value->argv[pos->i][pos->j
		+ 1] == '$')
	{
		(ft_bzero(pid_str, sizeof(char *)), get_pid_as_string(pid_str));
		value->argv[pos->i] = ft_str_replace(value->argv[pos->i], "$$",
				pid_str);
	}
	else if (value->argv[pos->i][pos->j] == '$' && value->argv[pos->i][pos->j
		+ 1] != '$')
		if (expend_variable_from_env(value, &pos->i, pos->j,
				is_quoted) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

static int	expend_value(t_minishell *shell_data, t_ast_value *value,
		t_pos *pos)
{
	bool	is_quoted;

	is_quoted = false;
	while (value->argv[pos->i] && value->argv[pos->i][pos->j])
	{
		is_quoted = is_in_dquote(&value->argv[pos->i][pos->j], is_quoted);
		if (value->argv[pos->i][pos->j] == (char)('\'' * -1) && !is_quoted)
			pos->j += pos_next_quote(
					&value->argv[pos->i][pos->j + 1], '\'' * -1) + 1;
		if (value->argv[pos->i][pos->j] == '$' && !(value->argv[pos->i][pos->j
				+ 1] == (char)('"' * -1) || value->argv[pos->i][pos->j
				+ 1] == '\0'))
		{
			if (expend_variable(shell_data, value, pos, is_quoted) == FAILURE)
				return (FAILURE);
		}
		else if (value->argv[pos->i][pos->j] == '~')
			(expend_tild(shell_data, value, pos), ++pos->j);
		else if (value->argv[pos->i][pos->j] == '*')
			return (expend_wildcard(shell_data, value->argv[pos->i]), WILDCARD);
		else
			++pos->j;
	}
	return (SUCCESS);
}

static int	add_to_chain_list(t_minishell *shell_data, t_ast_value *value,
		t_pos *pos)
{
	t_dlist	*tmp;
	int		ret;

	while (pos->i < value->argc && value->argv[pos->i])
	{
		pos->j = 0;
		ret = expend_value(shell_data, value, pos);
		if (ret != FAILURE)
		{
			tmp = new_dlist(value->argv[pos->i]);
			if (!tmp)
				return (free_dlist(&shell_data->stack), FAILURE);
			if (ret != WILDCARD)
				add_dlist(&shell_data->stack, tmp);
			else
				free_dlist(&tmp);
		}
		else if (ret == FAILURE)
			return (FAILURE);
		++pos->i;
	}
	return (SUCCESS);
}

int	expend(t_minishell *shell_data, t_ast_value *value)
{
	t_pos	pos;
	char	**argv_tmp;

	ft_bzero(&pos, sizeof(t_pos));
	free_dlist(&shell_data->stack);
	if (value->argv)
	{
		pos.i = 0;
		if (add_to_chain_list(shell_data, value, &pos) == FAILURE)
			return (free_dlist(&shell_data->stack), FAILURE);
		free_str_tab(value->argv);
		split_stack_elements(&shell_data->stack);
		value->argc = dlist_len(shell_data->stack);
		argv_tmp = dlist_to_argv(&shell_data->stack);
		if (argv_tmp == NULL)
			return (free_dlist(&shell_data->stack), FAILURE);
		free_dlist(&shell_data->stack);
		value->argv = argv_tmp;
		value->name = value->argv[0];
	}
	return (SUCCESS);
}
