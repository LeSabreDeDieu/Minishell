/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:31:50 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/17 16:18:40 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "minishell.h"
#include "tokens.h"

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
	const char	*token_names[9] = {"AND", "OR", "SUBSHELL", "WORD", "VARIABLE",
			"PIPE", "REDIRECTION", "DOUBLE_QUOTE", "SIMPLE_QUOTE"};

	if (!ast)
		return ;
	print_ast(ast->left);
	print_ast(ast->right);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	**v_argv;
	t_ast_value test;
	t_redirection_list redir_list[3] = {NULL, NULL, NULL};
	t_redirection redir[3] = {NULL, NULL, NULL};

	redir[0].filename = "pp1";
	redir[0].flag = READ;
	redir[1].filename = "pp2";
	redir[1].flag = READ;
	redir[2].filename = "pp3";
	redir[2].flag = READ;
	redir_list[0].next = &redir_list[1];
	redir_list[1].next = &redir_list[2];
	redir_list[0].redirection = &redir[0];
	redir_list[1].redirection = &redir[1];
	redir_list[2].redirection = &redir[2];
	(void)argc;
	(void)argv;
	create_env(envp);
	if (!test_env_config())
		return (0);
	ft_bzero(&test, sizeof(test));
	ft_putendl_fd("Welcome to minishell", 1);
	test.redirections = &redir_list[0];
	while (true)
	{
		line = rl_gets();
		printf("%p\n", line);
		if (!line)
			exit_command(1, NULL);
		to_tokenise(line, false);
		v_argv = ft_split(line, ' ');
		free(line);
		test.argv = v_argv;
		test.name = v_argv[0];
		test.argc = len_array(v_argv);
		print_token();
		execute_simple(&test, envp);
		free_str_tab(v_argv);
		// printf("\n");
		// get_ast_factory()->ast = create_ast(get_token_factory()->token_list);
		free_token();
	}
	return (0);
}
