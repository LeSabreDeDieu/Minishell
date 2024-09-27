/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:03:24 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/27 11:37:16 by sgabsi           ###   ########.fr       */
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
		expend_variable_from_env(value, pos->i, &pos->j);
}

static int	expend2(t_minishell *shell_data, t_ast_value *value, t_pos *pos)
{
	bool	is_quoted;

	is_quoted = false;
	while (value->argv[pos->i] && value->argv[pos->i][pos->j])
	{
		is_quoted = is_in_dquote(value->argv[pos->i][pos->j], is_quoted);
		if (value->argv[pos->i][pos->j] == '$')
		{
			expend_variable(shell_data, value, is_quoted, pos);
			pos->j += 2;
		}
		else if (value->argv[pos->i][pos->j] == '~')
		{
			expend_tild(shell_data, value, pos);
			++pos->j;
		}
		else if (value->argv[pos->i][pos->j] == '*')
		{
			expend_wildcard(shell_data, &value->argv);
			return (FAILURE);
		}
		else
			++pos->j;
	}
	return (SUCCESS);
}

int	expend(t_minishell *shell_data, t_ast_value *value)
{
	t_pos	pos;

	ft_bzero(&pos, sizeof(t_pos));
	shell_data->stack = NULL;
	pos.i = 0;
	while (value->argv[pos.i] && pos.i < value->argc)
	{
		pos.j = 0;
		if (expend2(shell_data, value, &pos) != FAILURE)
			add_stack(&shell_data->stack, new_stack(value->argv[pos.i]));
		++pos.i;
	}
	free_str_tab(value->argv);
	value->argc = stack_len(shell_data->stack);
	value->argv = stack_to_argv(&shell_data->stack);
	return (SUCCESS);
}
