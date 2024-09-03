/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:29:33 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/03 13:42:23 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_tokens *tokens)
{
	t_token_list	*current;
	const char		*token_names[9] = {"AND", "OR", "SUBSHELL",
		"VARIABLES", "PIPE", "REDIRECTION", "DOUBLE_QUOTE",
		"SIMPLE_QUOTE", "WORD"};

	if (tokens->first_token == NULL)
		return ;
	current = tokens->first_token;
	printf("Tokenisation : \n");
	while (current)
	{
		printf("[%s] => %%%s%%\n", token_names[current->token->type],
			current->token->value);
		current = current->next;
	}
}

static void	print_ast_node(t_ast *ast)
{
	const char			*type_names[] = {"AND", "OR", "SUBSHELL", "PIPE", "CMD"};
	const char			*redi_type[] = {"HERE_DOC", "READ", "WRITE", "APPEND"};
	t_redirection_list	*tmp;
	size_t				index;

	if (!ast)
		return ;
	index = -1;
	print_ast_node(ast->left);
	printf("Type : %s\n", type_names[ast->type]);
	printf("Name : %s\n", ast->value.name);
	while (++index < (size_t)ast->value.argc)
		printf("argv[%zu] : %s\n", index, ast->value.argv[index]);
	tmp = ast->value.redirections;
	printf("Redirections : \n");
	while (tmp)
	{
		printf("\tRedirection type : %s\n", redi_type[tmp->redirection.flag]);
		printf("\tFilename : %s\n", tmp->redirection.filename);
		tmp = tmp->next;
	}
	print_ast_node(ast->right);
	printf("\n");
}

void	print_ast(t_ast *ast)
{
	printf("\nAST : \n");
	print_ast_node(ast);
}
