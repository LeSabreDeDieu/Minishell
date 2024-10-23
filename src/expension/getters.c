/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:52:22 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/23 13:54:40 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

char	*get_end(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (!(ft_isalnum(*tmp) || *tmp == '_'))
			break ;
		tmp++;
	}
	return (tmp);
}

void	get_pid_as_string(char *pid_str)
{
	int		fd;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		i;

	i = 0;
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (perror("open"));
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0)
		return (close(fd), perror("read"));
	buffer[bytes_read] = '\0';
	close(fd);
	while (buffer[i] != ' ' && buffer[i] != '\0')
	{
		if (i < (int) sizeof(pid_str) - 1)
			pid_str[i] = buffer[i];
		i++;
	}
}

int	pos_next_quote(char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		return (i);
	return (-1);
}
