/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:14:37 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/15 16:11:54 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <utmp.h>

void	set_env_from_void(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	set_env("PWD", pwd);
	free(pwd);
	set_env("SHLVL", "0");
	set_env("_", "/usr/bin/env");
}

char	*get_path(void)
{
	char	*path;
	char	*split;
	int		fd;

	fd = open("/etc/environment", O_RDONLY);
	if (fd == -1)
	{
		errno = ENOENT;
		return (NULL);
	}
	path = get_next_line(fd);
	if (path == NULL)
	{
		errno = ENOENT;
		return (close(fd), NULL);
	}
	split = ft_strstr(path, "=") + 1;
	if (split == NULL)
	{
		errno = ENOMEM;
		return (close(fd), NULL);
	}
	split = ft_strtrim(split, "\"\n");
	free(path);
	return (close(fd), split);
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

int	expend_and_dequote(t_minishell *data, t_ast *ast)
{
	if (!ast)
		return (SUCCESS);
	if (expend_and_dequote(data, ast->right) == FAILURE)
		return (FAILURE);
	if (ast->type == AST_CMD || ast->type == AST_SUBSHELL)
	{
		if (expend(data, &ast->value) == FAILURE)
			return (FAILURE);
		to_dequote(&ast->value);
		dequote_delimiter(ast->value.redirections);
	}
	if (expend_and_dequote(data, ast->left) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	print_welcome(void)
{
	ft_putstr_fd("Welcome to ", STDOUT_FILENO);
	ft_putstr_fd(SHELL_NAME, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}
