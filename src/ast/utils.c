/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:25:19 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/30 11:12:22 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int	is_and_or_pipe(t_token_list *tokens)
{
	if (tokens->token->type == TOKEN_AND || tokens->token->type == TOKEN_OR
		|| tokens->token->type == TOKEN_PIPE)
		return (1);
	else if (tokens->token->type != TOKEN_AND && tokens->token->type != TOKEN_OR
		&& tokens->token->type != TOKEN_PIPE)
		return (2);
	return (0);
}

void	create_nodes_special(t_token_list *tokens, t_ast *left,
		t_ast *ast)
{
	if (is_and_or_pipe(tokens) == 1)
	{
		ast->left = left;
		if (tokens->token->type == TOKEN_AND)
			ast->type = AST_AND;
		if (tokens->token->type == TOKEN_OR)
			ast->type = AST_OR;
		if (tokens->token->type == TOKEN_PIPE)
			ast->type = AST_PIPE;
		if (tokens->next)
			ast->right = create_nodes(tokens->next);
	}
	else if (is_and_or_pipe(tokens) == 2)
		ast->right = create_nodes(tokens);
}
