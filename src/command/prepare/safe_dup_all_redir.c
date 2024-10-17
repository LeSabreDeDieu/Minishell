/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_dup_all_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:46:27 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/14 15:09:11 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	safe_dup_all_redir(t_minishell *data, t_ast_value *value, int action_mini,
		int action_redir)
{
	if (dup_all_redir(value->redirections) == -1)
	{
		if (action_mini != -1)
			free_minishell(data, action_mini);
		if (action_redir != -1)
			close_all_redir(value, action_redir);
		return (FAILURE);
	}
	return (SUCCESS);
}
