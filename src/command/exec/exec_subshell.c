/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:29:24 by gcaptari          #+#    #+#             */
/*   Updated: 2024/09/23 11:41:57 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "env.h"
#include <fcntl.h>
#include <stdio.h>

int	handle_subshell_redirections(t_minishell *data, t_ast_value *value)
{
	if (open_all_redirection(value->redirections) == FAILURE)
		exit(errno);
	close_dup_standard(value);
	if (dup_all_redir(value->redirections) == -1)
	{
		close_all_redir(value, CLOSE_DUP_STD | CLOSE_FD_REDIR);
		free_minishell(data, FREE_ALL);
		exit(ENOENT);
	}
	return (SUCCESS);
}

void	execute_in_subshell(t_minishell *data, t_ast_value *value)
{
	char	*prompt;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (handle_subshell_redirections(data, value) == FAILURE)
		return ;
	prompt = ft_strdup(value->name);
	free_minishell(data, FREE_AST | FREE_TOKEN | FREE_PIPE);
	traitement(data, prompt);
	free_minishell(data, FREE_ALL);
	exit(errno);
}

int	fork_subshell(t_minishell *data, t_ast_value *value)
{
	value->pid = fork();
	if (value->pid < 0)
	{
		data->current_status = errno;
		fork_error_message(strerror(errno));
		return (FAILURE);
	}
	if (!value->pid)
		execute_in_subshell(data, value);
	return (SUCCESS);
}

int	execute_subshell(t_minishell *data, t_ast_value *value)
{
	dup_standard(value);
	if (fork_subshell(data, value) == FAILURE)
		return (FAILURE);
	close_all_redir(value, CLOSE_DUP_STD | CLOSE_PIPE);
	return (SUCCESS);
}
