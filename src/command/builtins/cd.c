/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:38:21 by gcaptari          #+#    #+#             */
/*   Updated: 2024/09/16 16:12:16 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "env.h"
#include "libft.h"

static void	generic_error_message(char *path, char *error)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

static int	cd_with_argmuntes(t_env *current_pwd, char *argv[])
{
	char	*cwd;
	char	*pwd;
	t_env	*old_pwd;

	current_pwd = get_env("PWD");
	if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		old_pwd = get_env("OLDPWD");
		if (!old_pwd || !old_pwd->value)
			return (ft_putstr_fd("sanic: cd: « OLDPWD » not set\n", 2), 1);
		if (chdir(old_pwd->value) == 0)
		{
			(ft_putstr_fd(old_pwd->value, 1), ft_putstr_fd("\n", 1),
				pwd = ft_strdup(old_pwd->value));
			return (set_env("OLDPWD", current_pwd->value), set_env("PWD", pwd),
				free(pwd), 0);
		}
	}
	else if (chdir(argv[1]) == 0)
	{
		if (current_pwd)
			set_env("OLDPWD", current_pwd->value);
		cwd = getcwd(NULL, 0);
		return (set_env("PWD", cwd), free(cwd), 0);
	}
	return (generic_error_message(argv[1], strerror(errno)), 1);
}

int	cd_command(int argc, char *argv[])
{
	t_env	*current_pwd;
	t_env	*home;

	current_pwd = get_env("PWD");
	if (argc == 1 || ft_strncmp(argv[1], "~", 2) == 0)
	{
		home = get_env("HOME");
		if (!home || !home->value)
			return (ft_putstr_fd("sanic: cd: « HOME » not set\n", 2), 125);
		if (chdir(home->value) == 0)
		{
			if (current_pwd)
				set_env("OLDPWD", current_pwd->value);
			set_env("PWD", home->value);
			return (0);
		}
		return (generic_error_message(home->value, strerror(errno)), 1);
	}
	else if (argc == 2)
	{
		return (cd_with_argmuntes(current_pwd, argv));
	}
	return (ft_putstr_fd("sanic: cd: too many arguments\n", 2), 36);
}
