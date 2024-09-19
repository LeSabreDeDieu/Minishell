/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 00:46:46 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/19 14:15:26 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

int	match(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
		return (match(pattern + 1, str) || (*str != '\0' && match(pattern, str
					+ 1)));
	if (*pattern == *str || *pattern == '?')
		return (match(pattern + 1, str + 1));
	return (0);
}

int	count_matching_files(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;
	bool			is_repo;
	char			*pattern_copy;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (-1);
	is_repo = false;
	if (pattern[ft_strlen(pattern) - 1] == '/')
	{
		is_repo = true;
		pattern_copy = ft_strndup(pattern, ft_strlen(pattern) - 1);
	}
	else
		pattern_copy = ft_strdup(pattern);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (match(pattern_copy, entry->d_name))
		{
			if (is_repo && entry->d_type == 4)
				count++;
			else
				if (entry->d_name[0] != '.' || pattern_copy[0] == '.')
				count++;
		}
	}
	closedir(dir);
	free(pattern_copy);
	return (count);
}

char	**realloc_argv(char **argv, int old_size, int new_size)
{
	char	**new_argv;
	int		i;
	int		j;

	new_argv = ft_calloc(new_size + 1, sizeof(char *));
	if (!new_argv)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	j = 0;
	while (i < old_size)
	{
		if (ft_strncmp(argv[i], "*", 1) != 0)
		{
			new_argv[j] = ft_strdup(argv[i]);
			free(argv[i]);
			argv[i] = NULL;
			j++;
		}
		i++;
	}
	free(argv);
	return (new_argv);
}

void	fill_result_list(const char *pattern, char **argv, int *argc)
{
	DIR				*dir;
	struct dirent	*entry;
	bool			is_repo;
	char			*pattern_copy;

	is_repo = false;
	pattern_copy = ft_strdup(pattern);
	if (pattern[ft_strlen(pattern) - 1] == '/')
	{
		pattern_copy = ft_strndup(pattern, ft_strlen(pattern) - 1);
		is_repo = true;
	}
	dir = opendir(".");
	if (!dir)
		return ;
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (match(pattern_copy, entry->d_name) && (entry->d_name[0] != '.'
				|| pattern_copy[0] == '.'))
		{
			if (is_repo && entry->d_type == 4)
				argv[*argc] = ft_strjoin(entry->d_name, "/");
			else if (is_repo && entry->d_type != 4)
				continue ;
			else
				argv[*argc] = ft_strdup(entry->d_name);
			if (!argv[*argc])
			{
				perror("strdup");
				closedir(dir);
				return ;
			}
			(*argc)++;
		}
	}
	free(pattern_copy);
	closedir(dir);
}

int	expand_wildcard(const char *pattern, char ***argv, int *argc)
{
	int		count;
	int		new_size;
	char	*pattern_copy;

	if (wildcard_in_quote((char *)pattern))
		return (SUCCESS);
	if (pattern[0] == '\0')
		return (SUCCESS);
	count = count_matching_files(pattern);
	if (count <= 0)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(" : no matches found: ", 2);
		ft_putendl_fd((char *) pattern, 2);
		return (FAILURE);
	}
	new_size = *argc + count;
	pattern_copy = ft_strdup(pattern);
	*argv = realloc_argv(*argv, *argc, new_size);
	if (!*argv)
		return (FAILURE);
	pattern = NULL;
	*argc -= 1;
	fill_result_list(pattern_copy, *argv, argc);
	free(pattern_copy);
	return (SUCCESS);
}
