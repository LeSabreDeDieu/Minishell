/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:31:50 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/08 13:04:32 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "command.h"
#include "ast.h"

static void	print_token(void)
{
	t_token_factory	*fac;
	t_token_list	*current;
	const char		*token_names[9] = {"AND", "OR", "SUBSHELL", "WORD",
		"VARIABLE", "PIPE", "REDIRECTION", "DOUBLE_QUOTE",
		"SIMPLE_QUOTE"};

	fac = get_token_factory();
	if (!fac)
		return ;
	if (fac->token_list == NULL)
		return ;
	current = fac->token_list;
	printf("Tokenisation : \n");
	while (current)
	{
		printf("[%s] => %%%s%%\n", token_names[current->token->type],
			current->token->value);
		if (!current->next)
			break ;
		current = current->next;
	}
}

static void	print_ast(t_ast *ast)
{
	const char		*token_names[9] = {"AND", "OR", "SUBSHELL", "WORD",
		"VARIABLE", "PIPE", "REDIRECTION", "DOUBLE_QUOTE",
		"SIMPLE_QUOTE"};

	if (!ast)
		return ;
	printf("AST : [%s] => %%%s%%\n", token_names[ast->token->type],
		ast->token->value);
	print_ast(ast->left);
	print_ast(ast->right);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	(void)argc;
	(void)argv;
	char *argv_v[5];

	if (!test_env_config())
		return (0);
	create_env(envp);
	ft_putendl_fd("Welcome to minishell", 1);
	argv_v[0] = "cd";
	argv_v[1] = "-fsdfsdfsdff";
	argv_v[2] = "dfsdfsdsdfsdff";
	argv_v[3] = "fgsfgdfg";
	argv_v[4] = NULL;
	echo_command(5, argv_v);
	while (true)
	{
		line = rl_gets();
		if (!line)
			exit_command();
		to_tokenise(line, false);
		free(line);
		pre_parse(&get_token_factory()->token_list);
		print_token();
		// printf("\n");
		// get_ast_factory()->ast = create_ast(get_token_factory()->token_list);
		print_ast(get_ast_factory()->ast);
		free_token();
	}
	return (0);
}
