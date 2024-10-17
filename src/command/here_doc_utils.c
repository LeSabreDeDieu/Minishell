/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:09:12 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/14 15:40:48 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

int	parent_precess_hd(t_minishell *minishell, int pid, int itterdoc,
		t_redirection_list *redir_list)
{
	char	*itterdoc_str;
	char	*here_doc_name;
	int		status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	close(redir_list->redirection.fd);
	redir_list->redirection.fd = -1;
	if (WIFSIGNALED(status))
		minishell->current_status = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		minishell->current_status = WEXITSTATUS(status);
	if (minishell->current_status == 130)
		return (FAILURE);
	itterdoc_str = ft_itoa(itterdoc);
	here_doc_name = ft_strjoin(HERE_DOC_PATH, itterdoc_str);
	free(itterdoc_str);
	free(redir_list->redirection.filename);
	redir_list->redirection.filename = here_doc_name;
	return (SUCCESS);
}

int	child_process_hd(t_minishell *minishell, t_redirection_list *redir_list)
{
	signal(SIGINT, ft_signal_heredoc);
	signal(SIGQUIT, SIG_IGN);
	return (here_doc(minishell, redir_list));
}

int	fork_hd(t_minishell *minishell, t_redirection_list *redir_list,
		int itterdoc)
{
	int	pid;

	if (create_and_open_heredoc_file(redir_list, itterdoc) == FAILURE)
		return (FAILURE);
	pid = fork();
	if (pid == -1)
		return (FAILURE);
	if (pid == 0)
		child_process_hd(minishell, redir_list);
	else
	{
		if (parent_precess_hd(minishell, pid, itterdoc,
				redir_list) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
