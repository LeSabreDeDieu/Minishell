/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 00:46:46 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/20 19:37:46 by sgabsi           ###   ########.fr       */
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
			if (is_repo && entry->d_type == 4 && entry->d_name[0] != '.')
				count++;
			else if (is_repo && entry->d_type == 4 && pattern_copy[0] == '.'
				&& entry->d_name[0] == '.')
				count++;
			else if (!is_repo && entry->d_name[0] != '.')
				count++;
			else if (!is_repo && pattern_copy[0] == '.'
				&& entry->d_name[0] == '.')
				count++;
		}
	}
	closedir(dir);
	free(pattern_copy);
	return (count);
}

int realloc_argv(char ***argv, int old_size, int new_size, int i)
{
	char	**new_argv;
	int		begin_fill;
	int		j;

	new_argv = ft_calloc(new_size + 1, sizeof(char *));
	if (!new_argv)
	{
		perror("malloc");
		return (0);
	}
	j = 0;
	while (i < old_size)
	{
		if (ft_strstr((*argv)[i], "*") == NULL)
		{
			new_argv[j] = ft_strdup((*argv)[i]);
			free((*argv)[i]);
			j++;
		}
		else
		{
			free((*argv)[i]);
			i++;
			break ;
		}
		i++;
	}
	begin_fill = j;
	j += new_size - old_size;
	while (j < new_size && i < old_size)
	{
		new_argv[j] = ft_strdup((*argv)[i]);
		free((*argv)[i]);
		i++;
		j++;
	}
	*argv = new_argv;
	return (begin_fill);
}

void	fill_result_list(const char *pattern, char **argv, int *argc, int new_size)
{
	DIR				*dir;
	struct dirent	*entry;
	bool			is_repo;
	char			*pattern_copy;

	printf("argv[%d] = %s\n", *argc, argv[*argc]);
	is_repo = false;
	if (pattern[ft_strlen(pattern) - 1] == '/')
	{
		pattern_copy = ft_strndup(pattern, ft_strlen(pattern) - 1);
		is_repo = true;
	}
	else
		pattern_copy = ft_strdup(pattern);
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

int	expand_wildcard(const char *pattern, char ***argv, int *argc, int i)
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
		return (wildcard_error_message(pattern), FAILURE);
	new_size = *argc + count;
	pattern_copy = ft_strdup(pattern);
	*argc = realloc_argv(argv, *argc, new_size, i);
	if (argc == 0)
		return (FAILURE);
	pattern = NULL;
	fill_result_list(pattern_copy, *argv, &i, new_size);
	free(pattern_copy);
	(*argc) = new_size;
	int j = -1;
	while (++j < new_size)
		printf("argv[%d] = %s\n", j, (*argv)[j]);
	return (SUCCESS);
}
