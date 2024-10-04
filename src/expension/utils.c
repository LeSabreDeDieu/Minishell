/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:24:32 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/03 14:39:55 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

bool	is_in_dquote(char c, bool is_quoted)
{
	if (c == '"' && is_quoted == false)
		return (true);
	else if (c == '"' && is_quoted == true)
		return (false);
	else
		return (is_quoted);
}

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

int	expend_variable_from_env(t_ast_value *value, int *i, int j)
{
	char	*to_exp;
	t_env	*env;
	char	*env_value;

	env_value = "";
	to_exp = ft_substr(value->argv[(*i)], j, ft_strlen(&value->argv[(*i)][(j)])
			- ft_strlen(get_end(value->argv[(*i)] + ((j) + 1))));
	env = get_env(to_exp + 1);
	if (env != NULL)
		env_value = env->value;
	value->argv[(*i)] = ft_str_replace(value->argv[(*i)], to_exp, env_value);
	free(to_exp);
	return (SUCCESS);
}

int	pos_next_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'')
		i++;
	return (i);
}
