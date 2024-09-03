
#include "ast.h"
#include "command.h"

// void test_execution_pipe(t_minishell *minishell, int *std_in, int *nb_pipe, t_ast *ast_left, t_ast *ast_right)
// {
// 	printf("before left : %i\n", *nb_pipe);
// 	if(ast_left->left && ast_left->right)
// 	{
// 		(*nb_pipe)++;
// 		test_execution_pipe(minishell, std_in, nb_pipe, ast_left->left, ast_left->right);
// 	}
// 	if(ast_left->type == AST_CMD)
// 	{
// 		printf("VXCV %i\n", *std_in);
// 		char **env = env_to_tab();
// 		if(!env)
// 			return ;
// 		execute_pipe(minishell, std_in, &ast_left->value, env);
// 		free_str_tab(env);
// 	}
// 	printf("after left & before right : %i\n", *nb_pipe);
// 	if(ast_right->type == AST_CMD)
// 	{
// 		printf("CVCXVCV %i\n", *std_in);
// 		char **env = env_to_tab();
// 		if(!env)
// 			return ;
// 		execute_pipe(minishell, std_in, &ast_right->value, env);
// 		free_str_tab(env);
// 		(*nb_pipe)--;
// 	}
// 	printf("after right : %i\n", *nb_pipe);
// 	if (*nb_pipe == 0){
// 		close(*std_in);
// 		printf("fini!!\n");
// 	}
// }

void test_execution_pipe(t_minishell *minishell, int *std_in, int *nb_pipe, t_ast *ast_current)
{
	if (!ast_current)
		return ;
	test_execution_pipe(minishell, std_in, nb_pipe, ast_current->left);
	if (ast_current->type == AST_CMD)
	{
		char **env = env_to_tab();
		if(!env)
			return ;
		execute_pipe(minishell, std_in, &ast_current->value, env);
		free_str_tab(env);
	}
	test_execution_pipe(minishell, std_in, nb_pipe, ast_current->right);
	if (ast_current->value.last_cmd)
		close(*std_in);
}

int	test_execution(t_minishell *minishell, t_ast *ast, bool on_pipe)
{
	int result = 0;
	int std_in = -1;
	int pipe = 0;
	if (ast->type == AST_PIPE)
	{
		test_execution_pipe(minishell, &std_in, &pipe, ast);
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
		result = execute_simple(minishell, &ast->value);
	} else if(ast->type == AST_SUBSHELL)
	{
		result = execute_subshell(minishell, &ast->value);
	}
	return result;
}
