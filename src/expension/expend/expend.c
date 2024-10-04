/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:03:24 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/04 16:45:16 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

static void	expend_variable(t_minishell *shell_data, t_ast_value *value,
		bool is_quoted, t_pos *pos)
{
	char	pid_str[16];

	if (value->argv[pos->i][pos->j] == '\'' && !is_quoted)
		pos->j += pos_next_quote(&value->argv[pos->i][pos->j + 1]) + 1;
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
		expend_variable_from_env(value, &pos->i, pos->j);
}

static int	expend3(t_minishell *shell_data, t_ast_value *value, t_pos *pos)
{
	bool	is_quoted;

	is_quoted = false;
	while (value->argv[pos->i] && value->argv[pos->i][pos->j])
	{
		is_quoted = is_in_dquote(value->argv[pos->i][pos->j], is_quoted);
		if (value->argv[pos->i][pos->j] == '$')
		{
			expend_variable(shell_data, value, is_quoted, pos);
		}
		else if (value->argv[pos->i][pos->j] == '~')
		{
			expend_tild(shell_data, value, pos);
			++pos->j;
		}
		else if (value->argv[pos->i][pos->j] == '*')
		{
			expend_wildcard(shell_data, value->argv[pos->i]);
			return (FAILURE);
		}
		else
			++pos->j;
	}
	return (SUCCESS);
}

static int	expend2(t_minishell *shell_data, t_ast_value *value, t_pos *pos)
{
	t_dlist	*tmp;

	while (pos->i < value->argc && value->argv[pos->i])
	{
		pos->j = 0;
		if (expend3(shell_data, value, pos) != FAILURE)
		{
			tmp = new_dlist(value->argv[pos->i]);
			if (!tmp)
				return (free_dlist(&shell_data->stack), FAILURE);
			add_dlist(&shell_data->stack, tmp);
		}
		++pos->i;
	}
	return (SUCCESS);
}

int	expend(t_minishell *shell_data, t_ast_value *value)
{
	t_pos	pos;

	ft_bzero(&pos, sizeof(t_pos));
	shell_data->stack = NULL;
	if (value->argv)
	{
		pos.i = 0;
		expend2(shell_data, value, &pos);
		free_str_tab(value->argv);
		split_stack_elements(&shell_data->stack);
		value->argc = dlist_len(shell_data->stack);
		value->argv = dlist_to_argv(&shell_data->stack);
		value->name = value->argv[0];
	}
	return (SUCCESS);
}
