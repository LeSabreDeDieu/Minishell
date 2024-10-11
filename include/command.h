/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:08:49 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/11 17:21:57 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdlib.h>
# include <errno.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <string.h>

# include "ast.h"
# include "expension.h"
# include "ms_error.h"

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

// BUILDINS
int		echo_command(int argc, char *argv[]);
int		export_command(int argc, char *argv[]);
int		unset_command(int argc, char *argv[]);
int		env_command(int argc, char *argv[]);
int		cd_command(int argc, char *argv[]);
int		exit_command(t_minishell *minishell, int argc, char *argv[]);
int		pwd_command(int argc, char *argv[]);
int		history_command(t_minishell *minishell, int argc, char *argv[]);
int		exceve_builtins(t_minishell *minishell, char *name, int argc,
			char *argv[]);

// FOR COMMAND
int		execute_simple(t_minishell *minishell, t_ast_value *value);
void	execute_in_subshell(t_minishell *data, t_ast_value *value);
int		execute_subshell(t_minishell *data, t_ast_value *value);
void	execute_pipe(t_minishell *minishell, int *pipe_int, t_ast_value *value);
void	execute_pipe_last(t_minishell *minishell, int *pipe_int,
			t_ast_value *value);
void	execute_pipe_sub_last(t_minishell *minishell, int *pipe_int,
			t_ast_value *value);
void	execute_pipe_sub(t_minishell *minishell, int *pipe_in, t_ast_value *value);
void	execute_on_ast(t_minishell *minishell, t_ast *ast);
int		execute_builout(t_minishell *minishell, t_ast_value *value);
char	*get_real_command(char *name, t_minishell *minishell);
int		create_pipe(t_ast_value *value);
void	dup_standard(t_ast_value *value);
void	close_dup_standard(t_ast_value *value);

// UTILS
bool	is_builtin(char *name);
bool	is_exact_name(char *name, char *equal);
char	*special_cmd_join(char *path, char *name);

#endif
