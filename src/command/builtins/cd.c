/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:38:21 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/04 18:14:46 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "env.h"
#include "libft.h"
#include <string.h>

static int	cd_old_pwd(char *pwd, t_env *current_pwd)
{
	t_env	*old_pwd;

	old_pwd = get_env("OLDPWD");
	if (!old_pwd || !old_pwd->value)
		return (error_message_command("cd", OLDPWD_NOT_SET), FAILURE);
	if (chdir(old_pwd->value) == 0)
	{
		(ft_putstr_fd(old_pwd->value, 1), ft_putstr_fd("\n", 1),
			pwd = ft_strdup(old_pwd->value));
		return (set_env("OLDPWD", current_pwd->value), set_env("PWD", pwd),
			free(pwd), SUCCESS);
	}
	return (error_message_command_with_arg("cd", old_pwd->value,
			strerror(errno)), FAILURE);
}

static int	cd_with_argmuntes(t_env *current_pwd, char *argv[])
{
	char	*cwd;
	char	*pwd;

	current_pwd = get_env("PWD");
	pwd = NULL;
	if (ft_strncmp(argv[1], "-", 2) == 0)
		return (cd_old_pwd(pwd, current_pwd));
	else if (chdir(argv[1]) == 0)
	{
		if (current_pwd)
			set_env("OLDPWD", current_pwd->value);
		cwd = getcwd(NULL, 0);
		return (set_env("PWD", cwd), free(cwd), 0);
	}
	return (error_message_command_with_arg("cd", argv[1], strerror(errno)), 1);
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
			return (error_message_command("cd", HOME_NOT_SET), 125);
		if (chdir(home->value) == 0)
		{
			if (current_pwd)
				set_env("OLDPWD", current_pwd->value);
			set_env("PWD", home->value);
			return (0);
		}
		return (error_message_command_with_arg("cd", home->value,
				strerror(errno)), 1);
	}
	else if (argc == 2)
		return (cd_with_argmuntes(current_pwd, argv));
	return (error_message_command("cd", TOO_MANY_ARGUMENTS), 36);
}
