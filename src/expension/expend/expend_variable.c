/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:21:33 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/08 16:53:15 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

void	expend_last_status(t_minishell *shell_data, t_ast_value *value,
		t_pos *pos)
{
	char	*status;

	status = ft_itoa(shell_data->current_status);
	value->argv[pos->i] = ft_str_replace(value->argv[pos->i], "$?", status);
	free(status);
}

void	expend_tild(t_minishell *shell_data, t_ast_value *value, t_pos *pos)
{
	char	*tmp;
	char	*home;

	tmp = ft_strjoin("/home/", shell_data->data.username);
	home = ft_str_replace(value->argv[pos->i], "~", tmp);
	free(tmp);
	value->argv[pos->i] = home;
}
