/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:16:29 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/17 17:37:26 by sgabsi           ###   ########.fr       */
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
	int	i;

	if (!(*ast))
		return ;
	if ((*ast)->type == AST_CMD)
	{
		i = 0;
		if ((*ast)->value.argc != 0)
		{
			while (i < (*ast)->value.argc)
			{
				free((*ast)->value.argv[i]);
				i++;
			}
			free((*ast)->value.argv);
		}
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
