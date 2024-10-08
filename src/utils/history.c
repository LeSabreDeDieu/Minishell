/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:28:07 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/08 16:21:23 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>

static int	create_history(t_data_minishell *data)
{
	int		fd;
	char	*path;

	path = ft_strjoin(data->home, HISTORY_FILE);
	fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0666);
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
	fd = open(path, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		if (create_history(data) == FAILURE)
			return (FAILURE);
		fd = open(path, O_WRONLY | O_APPEND);
	}
	ft_putendl_fd(line, fd);
	close(fd);
	free(path);
	return (SUCCESS);
}

static void	get_all_lines(char *line, int fd)
{
	char	*tmp;

	while (line != NULL)
	{
		add_history(line);
		free(line);
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		line = ft_str_replace(tmp, "\n", "\0");
		if (line == NULL)
			free(tmp);
	}
}

int	read_history_from_file(t_data_minishell *data)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	*path;

	path = ft_strjoin(data->home, HISTORY_FILE);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		if (create_history(data) == FAILURE)
			return (FAILURE);
		fd = open(path, O_RDONLY);
	}
	tmp = get_next_line(fd);
	if (tmp == NULL)
	{
		close(fd);
		return (free(path), FAILURE);
	}
	line = ft_str_replace(tmp, "\n", "\0");
	if (line == NULL)
		return (close(fd), free(path), FAILURE);
	get_all_lines(line, fd);
	close(fd);
	return (free(path), SUCCESS);
}

int	clear_history_file(t_data_minishell *data)
{
	int		fd;
	char	*path;

	path = ft_strjoin(data->home, HISTORY_FILE);
	fd = open(path, O_TRUNC);
	if (fd == -1)
	{
		ft_putstr_fd("Error: can't clear history file\n", STDERR_FILENO);
		return (FAILURE);
	}
	close(fd);
	free(path);
	return (SUCCESS);
}
