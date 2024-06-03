/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:30:56 by gcaptari          #+#    #+#             */
/*   Updated: 2024/06/03 10:35:43 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "command.h"

t_command_manager	*get_command_mng(void)
{
	static volatile t_command_manager	manager;
	
	if (!manager.instanced)
	{
		manager.instanced = 1;
	}
	
	return (&manager);
}
