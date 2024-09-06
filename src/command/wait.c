/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:15:30 by gcaptari          #+#    #+#             */
/*   Updated: 2024/09/06 03:51:08 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_all_pid(t_ast *ast)
{
	if(!ast)
		return;
	kill_all_pid(ast->left);
	if(ast->value.pid != -1){
		kill(ast->value.pid, g_signal);
		ast->value.pid = -1;
	}
	kill_all_pid(ast->right);
}

void	wait_process(t_minishell *data, t_ast_value *value, bool is_pipeline)
{
	int ret;
	int states;
	ret = 0;
	while (ret >= 0)
	{
		ret = waitpid(value->pid, &states, WNOHANG);
			if(g_signal != 0){
			if(g_signal == SIGQUIT)
				ft_putendl_fd("\r^\\\033[0KQuit (Core dumped)", 1);
			kill_all_pid(data->ast);
			g_signal = 0;
			break;
		}
	}
	data->current_status = WEXITSTATUS(states);
	if (is_pipeline)
	{
		ret = 0;
		while (ret >= 0){
			ret = wait3(NULL,  WNOHANG, NULL);
			if(g_signal != 0){
				if(g_signal == SIGQUIT)
					ft_putendl_fd("\r^\\\033[0KQuit (Core dumped)", 1);
				kill_all_pid(data->ast);
				g_signal = 0;
				break;
			}
		}
		return;
	}
}
