/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:38:21 by gcaptari          #+#    #+#             */
/*   Updated: 2024/07/05 13:14:23 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "env.h"

int	cd_command(int argc, char *argv[])
{
	t_env	*current_pwd;
	char	*cwd;
	t_env	*home;

	if (argc == 2)
	{
		current_pwd = get_env("PWD");
		if (current_pwd)
			set_env("OLDPWD", current_pwd->value);
		home = get_env("HOME");
		if (!home)
			return (ft_putstr_fd("sanic: cd: HOME not set", 2), 125);
		if(chdir(home->value) == 0)
		{
			if (current_pwd)
				set_env("OLDPWD", current_pwd->value);
			set_env("PWD", home->value);
			return (0);
		}
		return (ft_putstr_fd("cd: /home/bocal/: Permission denied", 2), 1);
	}else if (argc == 3)
	{
		current_pwd = get_env("PWD");
		if(chdir(argv[2]) == 0)
		{
			if (current_pwd)
				set_env("OLDPWD", current_pwd->value);
			cwd = getcwd(NULL, 0);
			set_env("PWD", cwd);
			free(cwd);
			return (0);
		}
		return (ft_putstr_fd("cd: /home/bocal/: Permission denied", 2), 1);
	}
	return (ft_putstr_fd("bash: cd: too many arguments", 2), 36);
}