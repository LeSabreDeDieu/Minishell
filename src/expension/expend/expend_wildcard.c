/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:32:37 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/27 10:00:49 by sgabsi           ###   ########.fr       */
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

void	do_wildcard(t_stack **wildcard, char *pattern, DIR *dir)
{
	struct dirent	*entry;
	char			*pattern_copy;
	char			*tmp;
	char			*repo;
	int				i;

	repo = get_copy_pattern(pattern, &pattern_copy);
	entry = readdir(dir);
	i = 0;
	while (entry != NULL)
	{
		if (find_match(pattern_copy, entry->d_name) != -1)
		{
			add_file_wildcard(wildcard, pattern, entry, repo);
			i++;
		}
		entry = readdir(dir);
	}
	if (i == 0)
	{
		tmp = ft_strdup(pattern);
		add_stack(wildcard, new_stack(tmp));
		free(tmp);
	}
	free(pattern_copy);
}

int	add_matching_files(t_stack **wildcard, char *pattern)
{
	DIR	*dir;

	dir = opendir(".");
	if (!dir)
		return (FAILURE);
	do_wildcard(wildcard, pattern, dir);
	closedir(dir);
	return (SUCCESS);
}

int	expend_wildcard(t_minishell *shell_data, char ***argv, int *argc)
{
	DIR		*dir;
	int		i;

	i = 0;
	dir = opendir(".");
	if (!dir)
		return (FAILURE);
	while ((*argv)[i] != NULL)
	{
		if (ft_strchr((*argv)[i], '*'))
			add_matching_files(&shell_data->stack, (*argv)[i]);
		i++;
	}
	closedir(dir);
	return (SUCCESS);
}
