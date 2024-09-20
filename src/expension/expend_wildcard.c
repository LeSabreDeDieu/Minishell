/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:32:37 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/20 23:25:36 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

int match(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
		return (match(pattern + 1, str) || (*str != '\0' && match(pattern, str + 1)));
	if (*pattern == *str || *pattern == '?')
		return (match(pattern + 1, str + 1));
	return (0);
}

char **struct_to_argv(t_wildcard *wildcard)
{
	t_wildcard *tmp;
	char **argv;
	int i;

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

int	add_matching_files(t_wildcard **wildcard, const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*pattern_copy;
	bool			is_repo;
	char			*tmp;

	dir = opendir(".");
	if (!dir)
		return (FAILURE);
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
			{
				tmp = ft_strjoin(entry->d_name, "/");
				add_wildcard(wildcard, new_wildcard(tmp));
				free(tmp);
			}
			else if (is_repo && entry->d_type == 4 && pattern_copy[0] == '.'
				&& entry->d_name[0] == '.')
			{
				tmp = ft_strjoin(entry->d_name, "/");
				add_wildcard(wildcard, new_wildcard(tmp));
				free(tmp);
			}
			else if (!is_repo && entry->d_name[0] != '.')
				add_wildcard(wildcard, new_wildcard(entry->d_name));
			else if (!is_repo && pattern_copy[0] == '.'
				&& entry->d_name[0] == '.')
				add_wildcard(wildcard, new_wildcard(entry->d_name));
		}
		else
			return (closedir(dir), free(pattern_copy), FAILURE);
	}
	closedir(dir);
	free(pattern_copy);
	return (SUCCESS);
}

int expend_wildcard(char ***argv, int *argc)
{
	t_wildcard *wildcard;
	char	*last_wildcard;
	DIR *dir;
	int i;
	int last_i;

	i = 0;
	wildcard = NULL;
	dir = opendir(".");
	if (!dir)
		return (FAILURE);
	last_wildcard = NULL;
	while ((*argv)[i] != NULL)
	{
		if (last_wildcard == (*argv)[i] && i == last_i)
			break ;
		if (strchr((*argv)[i], '*'))
		{
			if (add_matching_files(&wildcard, (*argv)[i]) == FAILURE)
			{
				add_wildcard(&wildcard, new_wildcard((*argv)[i]));
				free((*argv)[i++]);
			}
			last_wildcard = (*argv)[i];
			last_i = i;
		}
		else
			add_wildcard(&wildcard, new_wildcard((*argv)[i]));
		free((*argv)[i]);
		i++;
	}
	while (argv[i])
	{
		add_wildcard(&wildcard, new_wildcard((*argv)[i]));
		free((*argv)[i]);
		i++;
	}
	(free((*argv)), closedir(dir));
	(*argc) = wildcard_len(wildcard);
	(*argv) = struct_to_argv(wildcard);
	return (SUCCESS);
}
