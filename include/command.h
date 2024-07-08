/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:08:49 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/08 10:23:37 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdbool.h>

typedef struct s_command
{
	char			*name;
	int				(*onexecute)(int argc, char *argv[]);
}					t_command;

typedef struct s_command_manager
{
	t_command		list_command[7];
	bool			instanced;
	int				(*dispatch)(char *name, int argc, char *argv[]);
	int				(*executebuiltout)(char *name, int argc, char *argv[]);
}					t_command_manager;

t_command_manager	*get_command_mng(void);

int					echo_command(int argc, char *argv[]);
int					unset_command(int argc, char *argv[]);
int					env_command(int argc, char *argv[]);
int					cd_command(int argc, char *argv[]);
void				exit_command(void);

#endif
