/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:08:49 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/20 11:08:55 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "ast.h"
# include "expension.h"
# include <errno.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>

typedef struct s_minishell			t_minishell;
typedef struct s_ast				t_ast;
typedef struct s_ast_value			t_ast_value;
typedef struct s_redirection_list	t_redirection_list;

typedef enum e_type_command
{
	BUILTIN,
	BUILTOUT
}									t_type_command;

typedef struct s_command
{
	char							*name;
	int								(*onexecute)(int argc, char *argv[]);
}									t_command;
typedef struct s_command_result
{
	int								status;
	t_type_command					type;
	__pid_t							pid;
	bool							pipe;
}									t_command_result;

int									echo_command(int argc, char *argv[]);
int									unset_command(int argc, char *argv[]);
int									env_command(int argc, char *argv[]);
int									cd_command(int argc, char *argv[]);
int									exit_command(t_minishell *minishell,
										int argc, char *argv[]);
int									exceve_builtins(t_minishell *minishell,
										char *name, int argc, char *argv[]);
int									execute_simple(t_minishell *minishell,
										t_ast_value *value);
void								execute_pipe(t_minishell *minishell,
										int *pipe_int, t_ast_value *value);
__pid_t								execute_pipe_last(t_minishell *minishell,
										int *pipe_int, t_ast_value *value,
										char *envp[]);
int									execute_subshell(t_minishell *data,
										t_ast_value *value);
void								test_execution(t_minishell *minishell,
										t_ast *ast);
char								*get_real_command(char *name,
										t_minishell *minishell);
bool								is_builtin(char *name);

int									create_pipe(t_ast_value *value);

void								here_doc(t_redirection_list **redir_list);

#endif
