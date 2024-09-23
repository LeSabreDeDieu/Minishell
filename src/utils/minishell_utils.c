/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:14:37 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/23 12:15:05 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utmp.h>

#include "minishell.h"

void	set_env_from_void(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	set_env("PWD", pwd);
	free(pwd);
	set_env("SHLVL", "0");
	set_env("_", "/usr/bin/env");
}

char	*get_uname(void)
{
	int			fd;
	struct utmp	user;
	char		*uname;

	fd = open("/var/run/utmp", O_RDONLY);
	if (fd == -1)
	{
		errno = ENOENT;
		return (NULL);
	}
	while (read(fd, &user, sizeof(struct utmp)) > 0)
	{
		if (user.ut_type == USER_PROCESS)
		{
			uname = ft_strdup(user.ut_name);
			if (uname == NULL)
			{
				close(fd);
				return (errno = ENOMEM, NULL);
			}
			return (close(fd), uname);
		}
	}
	close(fd);
	return (errno = ENOENT, NULL);
}

void	print_welcome(void)
{
	ft_putstr_fd("Welcome to ", STDOUT_FILENO);
	ft_putstr_fd(SHELL_NAME, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}
