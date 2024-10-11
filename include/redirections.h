/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:52:37 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/11 14:38:16 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

typedef struct s_ast_value		t_ast_value;
typedef struct s_ast			t_ast;
typedef struct s_minishell		t_minishell;

enum							e_close_fd
{
	CLOSE_FD_REDIR = 1 << 0,
	CLOSE_DUP_STD = 1 << 1,
	CLOSE_PIPE = 1 << 2,
	UNLINK = 1 << 3
};

typedef enum e_type_redirection
{
	HERE_DOC = 1,
	READ,
	WRITE,
	APPEND
}								t_type_redirection;

typedef struct s_redirection
{
	t_type_redirection			flag;
	int							fd;
	char						*filename;
}								t_redirection;

typedef struct s_redirection_list
{
	t_redirection				redirection;
	struct s_redirection_list	*next;
}								t_redirection_list;

int								open_all_redirection(t_redirection_list *list);
int								dup_all_redir(t_redirection_list *list);
void							close_all_redir(t_ast_value *value, int action);
int								safe_dup_all_redir(t_minishell *data,
									t_ast_value *value, int action_mini,
									int action_redir);
void							close_dup_standard(t_ast_value *value);
#endif
