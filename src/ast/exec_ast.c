
#include "ast.h"
#include "command.h"

void	test_execution_pipe(t_minishell *minishell, int *std_in, int *nb_pipe,
		t_ast *ast_current)
{
	char	**env;

	if (!ast_current)
		return ;
	test_execution_pipe(minishell, std_in, nb_pipe, ast_current->left);
	if (ast_current->type == AST_CMD)
	{
		env = env_to_tab();
		if (!env)
			return ;
		execute_pipe(minishell, std_in, &ast_current->value, env);
		free_str_tab(env);
		if (ast_current->value.last_cmd)
			close(*std_in);
	}
	test_execution_pipe(minishell, std_in, nb_pipe, ast_current->right);
}

int	test_execution(t_minishell *minishell, t_ast *ast, bool on_pipe)
{
	int	result;
	int	std_in;
	int	pipe;

	result = 0;
	std_in = -1;
	pipe = 0;
	if (ast->type == AST_PIPE)
	{
		test_execution_pipe(minishell, &std_in, &pipe, ast);
		return (0);
	}
	if (ast->right)
		result = test_execution(minishell, ast->right, ast->type == AST_PIPE);
	if (ast->type == AST_OR && result == 0)
		return (result);
	else if (ast->type == AST_AND && result != 0)
		return (result);
	if (ast->left)
		result = test_execution(minishell, ast->left, ast->type == AST_PIPE);
	if (ast->type == AST_CMD)
		result = execute_simple(minishell, &ast->value);
	else if (ast->type == AST_SUBSHELL)
		result = execute_subshell(minishell, &ast->value);
	return (result);
}
