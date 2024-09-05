/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:31:34 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/03 13:35:34 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast	*create_nodes(t_token_list *tokens)
{
	t_ast	*ast;
	t_ast	*right;

	if (tokens == NULL)
		return (NULL);
	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		return (NULL);
	right = ft_calloc(1, sizeof(t_ast));
	if (!right)
		return (free(ast), NULL);
	right->type = AST_CMD;
	if (tokens->token->type == TOKEN_SUBSHELL)
		right->type = AST_SUBSHELL;
	if (create_ast_value(&right->value, &tokens) == FAILURE)
		return (free(right), free(ast), NULL);
	if (tokens)
		create_nodes_special(tokens, right, ast);
	else
		return (free(ast), right);
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
