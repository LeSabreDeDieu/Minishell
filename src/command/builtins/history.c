/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:49:36 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/11 10:07:52 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"

static void	print_all_lines(char *line, int fd)
{
	char	*tmp;
	int		i;

	i = 1;
	while (line != NULL)
	{
		ft_putnbr_fd(i, STDOUT_FILENO);
		ft_putstr_fd("\t", STDOUT_FILENO);
		ft_putendl_fd(line, STDOUT_FILENO);
		free(line);
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		line = ft_str_replace(tmp, "\n", "\0");
		if (line == NULL)
			free(tmp);
		++i;
	}
}

int	print_history(t_data_minishell *data)
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
	print_all_lines(line, fd);
	close(fd);
	return (free(path), SUCCESS);
}

int	history_command(t_minishell *minishell, int argc, char *argv[])
{
	if (argc > 2)
		return (ft_putstr_fd("minishell: history: too many arguments\n",
				STDERR_FILENO), FAILURE);
	if (argc == 2)
	{
		if (ft_strncmp(argv[1], "-c", ft_strlen(argv[1])) == 0
			&& ft_strncmp(argv[1], "-c", ft_strlen("-c")) == 0)
		{
			clear_history_file(&minishell->data);
			return (SUCCESS);
		}
		return (ft_putstr_fd("minishell: history: invalid option\n",
				STDERR_FILENO), FAILURE);
	}
	if (print_history(&minishell->data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
