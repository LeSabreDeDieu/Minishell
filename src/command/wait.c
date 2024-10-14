/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:15:30 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/14 15:11:43 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_signal.h"

void	kill_all_pid(t_ast *ast)
{
	if (!ast)
		return ;
	kill_all_pid(ast->left);
	if (ast->type == AST_CMD && ast->value.pid != -1)
	{
		kill(ast->value.pid, g_signal);
		ast->value.pid = -1;
	}
	kill_all_pid(ast->right);
}

void	handle_signal_interrupt(t_minishell *data)
{
	if (g_signal == SIGQUIT)
		ft_putendl_fd("\033[0KQuit (Core dumped)", STDOUT_FILENO);
	else if (g_signal == SIGINT && data->current_status != 130)
		ft_putendl_fd("", STDOUT_FILENO);
	kill_all_pid(data->ast);
}

void	wait_for_single_process(t_minishell *data, t_ast_value *value)
{
	int	ret;
	int	states;

	ret = waitpid(value->pid, &states, 0);
	if (WIFSIGNALED(states))
	{
		data->current_status = (128 + WTERMSIG(states));
		if (WTERMSIG(states) == SIGQUIT)
			ft_putendl_fd("\033[0KQuit (Core dumped)", STDOUT_FILENO);
		else if (WTERMSIG(states) == SIGINT)
			ft_putendl_fd("", STDOUT_FILENO);
	}
	else if (WIFEXITED(states))
	{
		data->current_status = WEXITSTATUS(states);
	}
}

void	wait_for_pipeline(t_minishell *data)
{
	int	ret;

	(void)data;
	ret = 1;
	while (ret > 0)
	{
		ret = wait3(NULL, 0, NULL);
		if (g_signal != 0)
		{
			handle_signal_interrupt(data);
			break ;
		}
	}
}

void	wait_process(t_minishell *data, t_ast_value *value, bool is_pipeline)
{
	if (value->pid != -1)
		wait_for_single_process(data, value);
	if (is_pipeline)
	{
		wait_for_pipeline(data);
		ast_unlink_heredoc(data->ast);
	}
	else
		ast_unlink_heredoc(data->ast);
}
