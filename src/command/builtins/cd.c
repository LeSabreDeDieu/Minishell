/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:38:21 by gcaptari          #+#    #+#             */
/*   Updated: 2024/07/08 13:03:30 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "env.h"

static	void	generic_error_message(char *path, char *error)
{
	ft_putstr_fd("sanic: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

int	cd_command(int argc, char *argv[])
{
	t_env	*current_pwd;
	char	*cwd;
	t_env	*home;

	if (argc == 1)
	{
		current_pwd = get_env("PWD");
		if (current_pwd)
			set_env("OLDPWD", current_pwd->value);
		home = get_env("HOME");
		if (!home)
			return (ft_putstr_fd("sanic: cd: HOME not set\n", 2), 125);
		if(chdir(home->value) == 0)
		{
			if (current_pwd)
				set_env("OLDPWD", current_pwd->value);
			set_env("PWD", home->value);
			return (0);
		}
		return (generic_error_message(home->value, strerror(errno)), 1);
	}else if (argc == 2)
	{
		current_pwd = get_env("PWD");
		if(chdir(argv[1]) == 0)
		{
			if (current_pwd)
				set_env("OLDPWD", current_pwd->value);
			cwd = getcwd(NULL, 0);
			set_env("PWD", cwd);
			free(cwd);
			return (0);
		}
		return (generic_error_message(argv[1], strerror(errno)), 1);
	}
	return (ft_putstr_fd("sanic: cd: too many arguments\n", 2), 36);
}
