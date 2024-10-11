/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:28:07 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/11 10:44:40 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <readline/history.h>
#include <unistd.h>

int	create_history(t_data_minishell *data)
{
	int		fd;
	char	*path;

	path = ft_strjoin(data->home, HISTORY_FILE);
	fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error: can't create history file\n", STDERR_FILENO);
		return (FAILURE);
	}
	close(fd);
	free(path);
	return (SUCCESS);
}

int	add_history_file(t_data_minishell *data, char *line)
{
	int		fd;
	char	*path;

	add_history(line);
	path = ft_strjoin(data->home, HISTORY_FILE);
	if (path == NULL)
	{
		ft_putstr_fd("Error: can't add history file\n", STDERR_FILENO);
		return (ENOMEM);
	}
	fd = open(path, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		if (create_history(data) == FAILURE)
			return (errno);
		fd = open(path, O_WRONLY | O_APPEND);
		if (fd == -1)
			return (ft_putstr_fd("Error: can't read history file\n",
					STDERR_FILENO), errno);
	}
	ft_putendl_fd(line, fd);
	close(fd);
	free(path);
	return (SUCCESS);
}

static int	get_all_lines(int fd)
{
	char	*tmp;
	char	*line;

	tmp = get_next_line(fd);
	if (tmp == NULL)
		return (ENOMEM);
	line = ft_str_replace(tmp, "\n", "\0");
	if (line == NULL)
		return (ENOMEM);
	while (line != NULL)
	{
		add_history(line);
		free(line);
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		line = ft_str_replace(tmp, "\n", "\0");
		if (line == NULL)
			return (errno);
	}
	return (SUCCESS);
}

int	read_history_from_file(t_data_minishell *data)
{
	int		fd;
	char	*path;

	path = ft_strjoin(data->home, HISTORY_FILE);
	if (path == NULL)
	{
		ft_putstr_fd("Error: can't read history file\n", STDERR_FILENO);
		return (ENOMEM);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		if (create_history(data) == FAILURE)
			return (errno);
		fd = open(path, O_RDONLY);
		if (fd == -1)
			return (ft_putstr_fd("Error: can't read history file\n",
					STDERR_FILENO), errno);
	}
	if (get_all_lines(fd) != SUCCESS)
		return (close(fd), free(path), errno);
	close(fd);
	return (free(path), SUCCESS);
}

int	clear_history_file(t_data_minishell *data)
{
	int		fd;
	char	*path;

	path = ft_strjoin(data->home, HISTORY_FILE);
	if (path == NULL)
	{
		ft_putstr_fd("Error: can't clear history file\n", STDERR_FILENO);
		return (ENOMEM);
	}
	fd = open(path, O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error: can't clear history file\n", STDERR_FILENO);
		return (errno);
	}
	close(fd);
	free(path);
	return (SUCCESS);
}
