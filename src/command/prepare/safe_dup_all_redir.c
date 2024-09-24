/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_dup_all_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:46:27 by gcaptari          #+#    #+#             */
/*   Updated: 2024/09/23 11:46:42 by gcaptari         ###   ########.fr       */
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
