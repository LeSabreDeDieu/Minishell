/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:39:06 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/16 16:10:08 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "minishell.h"
#include "ms_signal.h"

static void	execution_by_type(t_minishell *shell_data, int *std_in,
		t_ast *ast_current)
{
	if (ast_current->type == AST_CMD || ast_current->type == AST_SUBSHELL)
	{
		if (ast_current->value.last_cmd)
		{
			execute_pipe_last(shell_data, std_in, &ast_current->value);
			wait_process(shell_data, &ast_current->value, true);
		}
		else
			execute_pipe(shell_data, std_in, &ast_current->value);
	}
}

void	execution_pipe(t_minishell *shell_data, int *std_in, t_ast *ast_current)
{
	if (!ast_current)
		return ;
	execution_pipe(shell_data, std_in, ast_current->right);
	execution_by_type(shell_data, std_in, ast_current);
	execution_pipe(shell_data, std_in, ast_current->left);
}

void	execute_on_ast(t_minishell *shell_data, t_ast *ast)
{
	int	std_in;

	if (!ast)
		return ;
	signal(SIGINT, ft_signal_child);
	signal(SIGQUIT, ft_signal_child);
	std_in = -1;
	if (ast->type == AST_PIPE)
	{
		execution_pipe(shell_data, &std_in, ast);
		return ;
	}
	if (ast->right)
		execute_on_ast(shell_data, ast->right);
	if ((ast->type == AST_OR && shell_data->current_status == 0)
		|| (ast->type == AST_AND && shell_data->current_status != 0))
		return ;
	if (ast->type == AST_CMD)
		execute_simple(shell_data, &ast->value);
	else if (ast->type == AST_SUBSHELL)
		execute_subshell(shell_data, &ast->value);
	wait_process(shell_data, &ast->value, false);
	if (ast->left)
		execute_on_ast(shell_data, ast->left);
}
