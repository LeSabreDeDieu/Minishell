/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:16:29 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/15 12:58:29 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	free_redirection_list(t_ast_value *value, t_redirection_list *list)
{
	t_redirection_list	*tmp;

	while (list)
	{
		if (list->redirection.fd != -1 && close(list->redirection.fd) == -1)
			error_message_command("free_redir", strerror(errno));
		list->redirection.fd = -1;
		free(list->redirection.filename);
		tmp = list;
		list = list->next;
		free(tmp);
	}
	close_all_redir(value, CLOSE_DUP_STD);
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
