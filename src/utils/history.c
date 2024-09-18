/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:28:07 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/17 15:06:58 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		create_history(void)
{
	int		fd;

	fd = open("/tmp/.sanicshell_history", O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("Error: can't create history file\n", 2);
		return(FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int		add_history_file(char *line)
{
	int		fd;

	fd = open("/tmp/.sanicshell_history", O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		ft_putstr_fd("Error: can't open history file\n", 2);
		return(FAILURE);
	}
	ft_putendl_fd(line, fd);
	close(fd);
	add_history(line);
	return (SUCCESS);
}

int		read_history_from_file(void)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open("/tmp/.sanicshell_history", O_RDONLY);
	if (fd == -1)
	{
		if (create_history() == FAILURE)
			return (FAILURE);
		fd = open("/tmp/.sanicshell_history", O_RDONLY);
	}
	line = ft_str_replace(get_next_line(fd), "\n", "\0");
	while (line != NULL)
	{
		add_history(line);
		free(line);
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		line = ft_str_replace(tmp, "\n", "\0");
	}
	close(fd);
	return (SUCCESS);
}

int		clear_history_file(void)
{
	int		fd;

	fd = open("/tmp/.sanicshell_history", O_TRUNC);
	if (fd == -1)
	{
		ft_putstr_fd("Error: can't clear history file\n", 2);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

