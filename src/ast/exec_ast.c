
#include "ast.h"
#include "command.h"
#include "minishell.h"

void	test_execution_pipe(t_minishell *minishell, int *std_in, t_ast *ast_current)
{
	char	**env;
	int		ret;

	if (!ast_current)
		return ;
	test_execution_pipe(minishell, std_in, ast_current->right);
	if (ast_current->type == AST_CMD)
	{
		env = env_to_tab();
		if (!env)
			return ;
		if (ast_current->value.last_cmd)
			execute_pipe_last(minishell, std_in, &ast_current->value, env);
		else
			execute_pipe(minishell, std_in, &ast_current->value);
		free_str_tab(env);
	}
	else if (ast_current->type == AST_SUBSHELL)
	{
		// execute_subshell(minishell, &ast_current->value);
	}
	if (ast_current->value.last_cmd)
	{
		ret = 0;
		while(ret >= 0)
			ret = waitpid(ast_current->value.pid, &minishell->current_status, WNOHANG);
		minishell->current_status = WEXITSTATUS(minishell->current_status);
		ret = 0;
		while (ret >= 0){
			ret = wait3(NULL,WNOHANG /* | WEXITED */, NULL);
		}
	}
	test_execution_pipe(minishell, std_in, ast_current->left);
}

void	test_execution(t_minishell *minishell, t_ast *ast)
{
	int	std_in;
	int	pipe;

	std_in = -1;
	pipe = 0;
	if (ast->type == AST_PIPE)
	{
		test_execution_pipe(minishell, &std_in, ast);
		return ;
	}
	if (ast->right)
		test_execution(minishell, ast->right);
	if (ast->left)
		test_execution(minishell, ast->left);
	if ((ast->type == AST_OR && minishell->current_status == 0)
		|| (ast->type == AST_AND && minishell->current_status != 0))
		return ;
	if (ast->type == AST_CMD)
		execute_simple(minishell, &ast->value);
	else if (ast->type == AST_SUBSHELL)
		execute_subshell(minishell, &ast->value);
}
