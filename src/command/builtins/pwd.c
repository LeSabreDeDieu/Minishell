/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:10:54 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/07 17:28:37 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"

int	pwd_command(int argc, char *argv[])
{
	t_env	*current_pwd;

	(void)argc;
	(void)argv;
	current_pwd = get_env("PWD");
	if (!current_pwd)
	{
		return (FAILURE);
	}
	ft_putendl_fd(current_pwd->value, STDOUT_FILENO);
	return (SUCCESS);
}
