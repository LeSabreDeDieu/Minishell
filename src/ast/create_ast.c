/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:31:34 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/19 11:46:38 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static t_ast	*create_nodes(t_token_list *tokens)
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
	if (!left->type)
		return (free(left), free(ast), NULL);
	if (tokens && (tokens->token->type == TOKEN_AND
			|| tokens->token->type == TOKEN_OR
			|| tokens->token->type == TOKEN_PIPE))
	{
		ast->left = left;
		if (tokens->token->type == TOKEN_AND)
			ast->type = AST_AND;
		else if (tokens->token->type == TOKEN_OR)
			ast->type = AST_OR;
		else if (tokens->token->type == TOKEN_PIPE)
			ast->type = AST_PIPE;
		ft_bzero(&ast->value, sizeof(t_ast_value));
		if (tokens)
			ast->right = create_nodes(tokens->next);
	}
	else if (tokens && (tokens->token->type != TOKEN_AND
			|| tokens->token->type != TOKEN_OR
			|| tokens->token->type != TOKEN_PIPE))
		ast->right = create_nodes(tokens);
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
