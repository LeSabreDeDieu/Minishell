/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:16:29 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/30 10:38:56 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	free_redirection_list(t_redirection_list *list)
{
	t_redirection_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void	free_ast(t_ast **ast)
{
	if (!(*ast))
		return ;
	if ((*ast)->type == AST_CMD)
	{
		if ((*ast)->value.argc != 0)
			free((*ast)->value.argv);
		free_redirection_list((*ast)->value.redirections);
	}
	else
	{
		free_ast(&(*ast)->left);
		free_ast(&(*ast)->right);
	}
	free(*ast);
	*ast = NULL;
}
