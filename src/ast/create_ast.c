/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:31:34 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/30 10:36:04 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast	*create_nodes(t_token_list *tokens)
{
	t_ast	*ast;
	t_ast	*left;

	if (tokens == NULL)
		return (NULL);
	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		return (NULL);
	left = ft_calloc(1, sizeof(t_ast));
	if (!left)
		return (free(ast), NULL);
	left->type = AST_CMD;
	if (tokens->token->type == TOKEN_SUBSHELL)
		left->type = AST_SUBSHELL;
	if (create_ast_value(&left->value, &tokens) == FAILURE)
		return (free(left), free(ast), NULL);
	if (tokens)
		create_nodes_special(tokens, left, ast);
	else
		return (free(ast), left);
	return (ast);
}

int	create_ast(t_minishell *data, t_tokens *tokens)
{
	t_ast			*ast;
	t_token_list	*current;

	current = tokens->first_token;
	if (!current)
		return (FAILURE);
	ast = create_nodes(current);
	if (!ast)
		return (FAILURE);
	data->ast = ast;
	return (SUCCESS);
}
