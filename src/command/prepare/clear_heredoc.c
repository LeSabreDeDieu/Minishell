/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:35:42 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/11 18:40:30 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	unlink_heredoc(t_redirection_list *list)
{
	t_redirection_list	*current;

	current = list;
	while (current)
	{
		if (current->redirection.filename && current->redirection.flag == HERE_DOC)
			unlink(current->redirection.filename);
		current = current->next;
	}
}

void	ast_unlink_heredoc(t_ast *current)
{
	if(!current)
		return;
	ast_unlink_heredoc(current->left);
	if (current->type == AST_CMD || current->type == AST_SUBSHELL)
	{
		if(current->value.redirections)
			unlink_heredoc(current->value.redirections);
	}

	ast_unlink_heredoc(current->right);

}
