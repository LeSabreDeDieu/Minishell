/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:32:37 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/23 16:45:55 by sgabsi           ###   ########.fr       */
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

char	**struct_to_argv(t_wildcard *wildcard)
{
	t_wildcard	*tmp;
	char		**argv;
	int			i;

	argv = ft_calloc(wildcard_len(wildcard) + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	tmp = wildcard;
	while (tmp)
	{
		argv[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	free_wildcard(&wildcard);
	return (argv);
}

void	do_wildcard(t_wildcard **wildcard, char *pattern, DIR *dir)
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
		add_wildcard(wildcard, new_wildcard(tmp));
		free(tmp);
	}
	free(pattern_copy);
}

int	add_matching_files(t_wildcard **wildcard, char *pattern)
{
	DIR				*dir;

	dir = opendir(".");
	if (!dir)
		return (FAILURE);
	do_wildcard(wildcard, pattern, dir);
	closedir(dir);
	return (SUCCESS);
}

int	expend_wildcard(char ***argv, int *argc)
{
	t_wildcard	*wildcard;
	DIR			*dir;
	int			i;

	i = 0;
	wildcard = NULL;
	dir = opendir(".");
	if (!dir)
		return (FAILURE);
	while ((*argv)[i] != NULL)
	{
		if (ft_strchr((*argv)[i], '*'))
			add_matching_files(&wildcard, (*argv)[i]);
		else
			add_wildcard(&wildcard, new_wildcard((*argv)[i]));
		free((*argv)[i]);
		i++;
	}
	(free((*argv)), closedir(dir));
	(*argc) = wildcard_len(wildcard);
	(*argv) = struct_to_argv(wildcard);
	return (SUCCESS);
}
