/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:50:50 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/18 17:06:39 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "tokens.h"
#include "libft.h"
#include <stdio.h> 

static t_ast	*create_node(t_token *token)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static t_ast	*create_ast_rec(t_token_list **token)
{
	t_ast	*node;

	if (!*token)
		return (NULL);
	node = create_node((*token)->token);
	if (!node)
		return (NULL);
	*token = (*token)->next;
	if (*token == NULL)
		return (node);
	if ((*token)->token->type == TOKEN_AND || (*token)->token->type == TOKEN_OR)
	{
		*token = (*token)->next;
		if (*token == NULL)
			return (node);
		node->left = create_ast_rec(token);
		node->right = create_ast_rec(token);
	}
	else if ((*token)->token->type == TOKEN_PIPE)
	{
		*token = (*token)->next;
		if (*token == NULL)
			return (node);
		node->left = create_ast_rec(token);
	}
	return (node);
}

t_ast	*create_ast(t_token_list *token)
{
	t_ast	*ast;

	ast = create_ast_rec(&token);
	if (!ast)
		return (NULL);
	return (ast);
}
