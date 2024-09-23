/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:15:30 by gcaptari          #+#    #+#             */
/*   Updated: 2024/09/23 12:10:08 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_all_pid(t_ast *ast)
{
	if(!ast)
		return;
	kill_all_pid(ast->left);
	if(ast->value.pid != -1){
		kill(ast->value.pid, SIGCHLD);
		ast->value.pid = -1;
	}
	kill_all_pid(ast->right);
}

void handle_signal_interrupt(t_minishell *data)
{
	if (g_signal == SIGQUIT)
		ft_putendl_fd("\r^\\\033[0KQuit (Core dumped)", 1);
	kill_all_pid(data->ast);
	g_signal = 0;
}

void wait_for_single_process(t_minishell *data, t_ast_value *value)
{
	int ret;
	int states;

	ret = 0;
	while (ret >= 0)
	{
		ret = waitpid(value->pid, &states, WNOHANG);
		if (g_signal != 0)
		{
			handle_signal_interrupt(data);
			break;
		}
	}
	data->current_status = WEXITSTATUS(states);
}

void wait_for_pipeline(t_minishell *data)
{
	int ret;

	ret = 0;
	while (ret >= 0)
	{
		ret = wait3(NULL, WNOHANG, NULL);
		if (g_signal != 0)
		{
			handle_signal_interrupt(data);
			break;
		}
	}
}

void wait_process(t_minishell *data, t_ast_value *value, bool is_pipeline)
{
	if (value->pid != -1)
		wait_for_single_process(data, value);
	if (is_pipeline)
		wait_for_pipeline(data);
}
