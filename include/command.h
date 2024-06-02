/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:08:49 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/02 18:26:57 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdbool.h>

typedef struct s_command
{
	char	*name;
	int		(*onexecute)(char *argv[]);
}				t_command;

typedef struct s_command_manager
{
	t_command	list_command[7];
	bool		instanced;
	int			(*dispatch)(char *name, char *argv[]);
	int			(*executebuiltout)(char *name, char *argv[]);
}				t_command_manager;

t_command_manager	*get_command_mng(void);

#endif