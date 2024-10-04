/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:16:29 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/03 13:05:18 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	free_redirection_list(t_ast_value *value, t_redirection_list *list)
{
	t_redirection_list	*tmp;

	while (list)
	{
		if (list->redirection.fd != -1)
			close(list->redirection.fd);
		free(list->redirection.filename);
		tmp = list;
		list = list->next;
		free(tmp);
	}
	if (value->fd_in != -1)
		close(value->fd_in);
	if (value->fd_out != -1)
		close(value->fd_out);
	value->fd_in = -1;
	value->fd_out = -1;
}

void	free_ast(t_ast **ast)
{
	int	i;

	if (!(*ast))
		return ;
	if ((*ast)->type == AST_CMD || (*ast)->type == AST_SUBSHELL)
	{
		i = 0;
		if ((*ast)->value.argv && (*ast)->value.argc)
		{
			while (i < (*ast)->value.argc)
			{
				free((*ast)->value.argv[i]);
				i++;
			}
			free((*ast)->value.argv);
		}
		free_redirection_list(&(*ast)->value, (*ast)->value.redirections);
	}
	else
	{
		free_ast(&(*ast)->left);
		free_ast(&(*ast)->right);
	}
	free(*ast);
	*ast = NULL;
}
