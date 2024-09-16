/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 00:46:46 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/12 01:40:22 by sgabsi           ###   ########.fr       */
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

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (-1);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (match(pattern, entry->d_name))
		{
			if (entry->d_name[0] != '.' || pattern[0] == '.')
				count++;
		}
	}
	closedir(dir);
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
			++j;
		}
		++i;
	}
	free(argv);
	return (new_argv);
}

void	fill_result_list(const char *pattern, char **argv, int *argc)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return ;
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (match(pattern, entry->d_name) && (entry->d_name[0] != '.'
				|| pattern[0] == '.'))
		{
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
	closedir(dir);
}

int	expand_wildcard(const char *pattern, char ***argv, int *argc)
{
	int	count;
	int	new_size;

	if (wildcard_in_quote((char *)pattern))
		return (SUCCESS);
	count = count_matching_files(pattern);
	if (count <= 0)
		return (FAILURE);
	new_size = *argc + count;
	*argv = realloc_argv(*argv, *argc, new_size);
	if (!*argv)
		return (FAILURE);
	fill_result_list(pattern, *argv, argc);
	free((char *)pattern);
	return (SUCCESS);
}
