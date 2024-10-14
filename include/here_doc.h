/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:16:59 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/14 15:15:51 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "minishell.h"
# include "ms_signal.h"
# include "utils.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define HERE_DOC_PATH "/tmp/.minishell_here_doc_"

typedef struct s_minishell			t_minishell;
typedef struct s_redirection_list	t_redirection_list;

int	parent_precess_hd(t_minishell *minishell, int pid, int itterdoc,
		t_redirection_list *redir_list);
int	child_process_hd(t_minishell *minishell, t_redirection_list *redir_list);
int	fork_hd(t_minishell *minishell, t_redirection_list *redir_list,
		int itterdoc);
int	here_doc(t_minishell *minishell, t_redirection_list *redir_list);
int	create_and_open_heredoc_file(t_redirection_list *redir_list, int itterdoc);
int	open_all_here_doc(t_minishell *minishell, t_ast *ast, int *itterdoc);

#endif