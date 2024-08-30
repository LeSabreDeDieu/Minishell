
#include "ast.h"
#include "command.h"

void test_execution_pipe(t_minishell *minishell, int *std_in, t_ast *ast_left, t_ast *ast_right)
{
	if(ast_left->left && ast_left->right)
		test_execution_pipe(minishell, std_in, ast_left->left, ast_left->right);
	if(ast_left->type == AST_CMD)
	{
		char ** env = env_to_tab();
		if (!env)
			return ;
		free_str_tab(env);
	}
	if(ast_right->left && ast_right->right)
		test_execution_pipe(minishell, std_in, ast_right->left, ast_right->right);
}

int	test_execution(t_minishell *minishell, t_ast *ast, bool on_pipe)
{
	int result = 0;
	int std_in = -1;
	if (ast->type == AST_PIPE)
	{
		test_execution_pipe(minishell, &std_in, ast->left, ast->right);
		return 0;
	}
	if(ast->left)
		result = test_execution(minishell, ast->left, ast->type == AST_PIPE);
	if(ast->type == AST_OR && result == 0)
		return result;
	else if(ast->type == AST_AND && result != 0)
		return result;
	if (ast->right)
		result = test_execution(minishell, ast->right, ast->type == AST_PIPE);
	if(ast->type == AST_CMD)
	{
		char ** env = env_to_tab();
		if (!env)
			return (-1);
		result = execute_simple(minishell, &ast->value, env);
		free_str_tab(env);
	} else if(ast->type == AST_SUBSHELL)
	{
		result = execute_subshell(minishell, &ast->value);
	}
	return result;
}
