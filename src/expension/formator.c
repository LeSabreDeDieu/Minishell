/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:16:19 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/10 16:52:02 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

char	*get_end(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (*tmp == ' ' || *tmp == '$' || *tmp == '\'' || *tmp == '"')
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
		if (i < (int)sizeof(pid_str) - 1)
			pid_str[i] = buffer[i];
		i++;
	}
}

void	expend_variable_from_env(t_ast_value *value, int i, int *j)
{
	char	*to_exp;
	t_env	*env;
	char	*env_value;

	env_value = "";
	to_exp = ft_substr(value->argv[i], *j, ft_strlen(&value->argv[i][(*j)])
			- ft_strlen(get_end(value->argv[i] + ((*j) + 1))));
	env = get_env(to_exp + 1);
	if (env != NULL)
		env_value = env->value;
	value->argv[i] = ft_str_replace(value->argv[i], to_exp, env_value);
	free(to_exp);
}

int	pos_next_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'')
	{
		i++;
	}
	return (i);
}

void	expend_variable(t_ast_value *value)
{
	int		i;
	int		j;
	char	pid_str[16];
	bool	is_quoted;

	if (!value || !value->argv || !value->argc)
		return ;
	i = 0;
	is_quoted = false;
	while (value->argv[i] && i < value->argc)
	{
		j = 0;
		while (value->argv[i][j])
		{
			is_quoted = is_in_quote(value->argv[i][j], is_quoted);
			if (value->argv[i][j] == '\'' && !is_quoted)
				j += pos_next_quote(&value->argv[i][j + 1]) + 1;
			if (value->argv[i][j] == '$' && value->argv[i][j + 1] == '$'
				&& !is_quoted)
			{
				ft_bzero(pid_str, sizeof(char *));
				get_pid_as_string(pid_str);
				value->argv[i] = ft_str_replace(value->argv[i], "$$", pid_str);
			}
			if (value->argv[i][j] == '$' && value->argv[i][j + 1] != '$'
				&& !is_quoted)
				expend_variable_from_env(value, i, &j);
			++j;
		}
		++i;
	}
	value->name = value->argv[0];
}
