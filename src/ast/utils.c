/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:25:19 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/05 14:19:43 by gcaptari         ###   ########.fr       */
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

static bool detect_is_final_cmd(t_token_list *list){
	t_token_list *mm;

	mm = list;
	if (!mm)
		return (false);
	while (mm)
	{
		if (mm->next && mm->next->token->type == TOKEN_PIPE)
			return (false);
		else if (!mm->next || mm->next->token->type == TOKEN_AND || mm->next->token->type == TOKEN_OR)
			return (true);
		mm = mm->next;
	}
	return (false);
}

void	create_nodes_special(t_token_list *tokens, t_ast *right,
		t_ast *ast)
{
	if (is_and_or_pipe(tokens) == 1)
	{
		ast->right = right;
		if (tokens->token->type == TOKEN_AND)
			ast->type = AST_AND;
		if (tokens->token->type == TOKEN_OR)
			ast->type = AST_OR;
		if (tokens->token->type == TOKEN_PIPE)
			ast->type = AST_PIPE;
		if (tokens->next)
			ast->left = create_nodes(tokens->next);
		if (ast->right  && detect_is_final_cmd(tokens->next))
			ast->left->value.last_cmd = true;
		else if (ast->left  && detect_is_final_cmd(tokens->next))
			ast->right->value.last_cmd = true;
	}
	else if (is_and_or_pipe(tokens) == 2)
		ast->left = create_nodes(tokens);
}
