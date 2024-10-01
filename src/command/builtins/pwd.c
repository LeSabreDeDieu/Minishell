/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:10:54 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/01 10:28:51 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"

int	pwd_command(int argc, char *argv[])
{
	t_env	*current_pwd;

	current_pwd = get_env("PWD");
	if (!current_pwd)
	{
		return (FAILURE);
	}
	ft_putendl_fd(current_pwd->value, STDOUT_FILENO);
	return (SUCCESS);
}
