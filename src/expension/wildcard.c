/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:22:26 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/10 22:45:09 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

int	match(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
		return (match(pattern + 1, str) || (*str != '\0' && match(pattern, str + 1)));
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
	while ((entry = readdir(dir)) != NULL)
	{
		if (match(pattern, entry->d_name))
			count++;
	}
	closedir(dir);
	return (count);
}

char	**realloc_argv(char **argv, int old_size, int new_size)
{
	char	**new_argv;
	int		i;

	new_argv = malloc(sizeof(char *) * new_size);
	if (!new_argv)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (i < old_size)
	{
		new_argv[i] = argv[i];
		i++;
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
		return;
	while ((entry = readdir(dir)) != NULL)
	{
		if (match(pattern, entry->d_name))
		{
			argv[*argc] = strdup(entry->d_name);
			if (!argv[*argc])
			{
				perror("strdup");
				return;
			}
			(*argc)++;
		}
	}
	closedir(dir);
}

void	expand_wildcard(const char *pattern, char ***argv, int *argc)
{
	int		count;
	int		new_size;

	count = count_matching_files(pattern);
	if (count == -1 || count == 0)
		return;
	new_size = *argc + count;
	*argv = realloc_argv(*argv, *argc, new_size);
	if (!*argv)
		return;
	fill_result_list(pattern, *argv, argc);
}
