/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:08:49 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/12 14:04:23 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "ast.h"
# include <errno.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>

typedef enum e_type_command
{
	BUILTIN,
	BUILTOUT
}					t_type_command;

typedef struct s_command
{
	char			*name;
	int				(*onexecute)(int argc, char *argv[]);
}					t_command;
typedef struct s_command_result
{
	int				status;
	t_type_command	type;
	__pid_t			pid;
	bool			pipe;
}					t_command_result;

typedef struct s_command_manager
{
	t_command		list_command[7];
	bool			instanced;
	int				(*dispatch)(char *name, int argc, char *argv[]);
}					t_command_manager;

t_command_manager	*get_command_mng(void);

int					echo_command(int argc, char *argv[]);
int					unset_command(int argc, char *argv[]);
int					env_command(int argc, char *argv[]);
int					cd_command(int argc, char *argv[]);
int					exit_command(int argc, char *argv[]);
int					execute_simple(t_ast_value *value, char *envp[]);
__pid_t				execute_pipe(t_ast_value *value, char *envp[]);
#endif
