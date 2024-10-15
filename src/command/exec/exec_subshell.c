/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:29:24 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/15 16:13:59 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "env.h"
#include "ms_signal.h"
#include <fcntl.h>
#include <stdio.h>

int	handle_subshell_redirections(t_minishell *data, t_ast_value *value)
{
	if (open_all_redirection(value->redirections) == FAILURE)
		exit(errno);
	if (dup_all_redir(value->redirections) == -1)
	{
		close_all_redir(value, CLOSE_FD_REDIR | UNLINK);
		free_minishell(data, FREE_ALL);
		exit(ENOENT);
	}
	return (SUCCESS);
}

void	execute_in_subshell(t_minishell *data, t_ast_value *value)
{
	char	*prompt;
	int		status;
	size_t	line;

	if (handle_subshell_redirections(data, value) == FAILURE)
		return ;
	line = ft_strlen(value->name);
	if (value->name && *value->name == '(' && value->name[line - 1] == ')')
		prompt = ft_substr(value->name, 1, line - 2);
	else
		prompt = ft_strdup(value->name);
	if (!prompt)
	{
		close_all_redir(value, CLOSE_FD_REDIR | UNLINK);
		free_minishell(data, FREE_ALL);
		exit(ENOMEM);
	}
	free_minishell(data, FREE_AST | FREE_TOKEN);
	status = traitement(data, prompt);
	free_minishell(data, FREE_ALL);
	exit(status);
}

int	fork_subshell(t_minishell *data, t_ast_value *value)
{
	value->pid = fork();
	if (value->pid < 0)
	{
		data->current_status = errno;
		error_message_command("fork", strerror(errno));
		return (FAILURE);
	}
	if (!value->pid)
	{
		g_signal = 0;
		execute_in_subshell(data, value);
	}
	return (SUCCESS);
}

int	execute_subshell(t_minishell *data, t_ast_value *value)
{
	if (fork_subshell(data, value) == FAILURE)
		return (FAILURE);
	close_all_redir(value, CLOSE_DUP_STD | CLOSE_PIPE);
	return (SUCCESS);
}
