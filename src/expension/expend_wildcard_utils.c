/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:59:22 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/23 16:30:36 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

static void	add_all(t_wildcard **wildcard, char *pattern, struct dirent *entry)
{
	char	*tmp;

	if (pattern[0] != '.' && entry->d_name[0] != '.')
	{
		tmp = ft_strdup(entry->d_name);
		add_wildcard(wildcard, new_wildcard(tmp));
		free(tmp);
	}
	else if (pattern[0] == '.' && entry->d_name[0] == '.')
	{
		tmp = ft_strdup(entry->d_name);
		add_wildcard(wildcard, new_wildcard(tmp));
		free(tmp);
	}
}

static void	add_repo(t_wildcard **wildcard, char *pattern, struct dirent *entry,
		char *repo)
{
	char	*tmp;

	if (pattern[0] != '.' && entry->d_name[0] != '.' && entry->d_type == 4)
	{
		tmp = ft_strjoin(entry->d_name, repo);
		add_wildcard(wildcard, new_wildcard(tmp));
		free(tmp);
	}
	else if (pattern[0] == '.' && entry->d_name[0] == '.' && entry->d_type == 4)
	{
		tmp = ft_strjoin(entry->d_name, repo);
		add_wildcard(wildcard, new_wildcard(tmp));
		free(tmp);
	}
}

void	add_file_wildcard(t_wildcard **wildcard, char *pattern,
		struct dirent *entry, char *repo)
{
	char	*tmp;

	if (repo == NULL)
		add_all(wildcard, pattern, entry);
	else if (ft_strnstr(repo, "/", 1) != NULL)
		add_repo(wildcard, pattern, entry, repo);
	else if (ft_strstr(repo, "./") != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			tmp = ft_strjoin(repo, entry->d_name);
			add_wildcard(wildcard, new_wildcard(tmp));
			free(tmp);
		}
	}
}

char	*get_copy_pattern(const char *pattern, char **pattern_copy)
{
	char	*repo;

	repo = NULL;
	if (pattern[ft_strlen(pattern) - 1] == '/')
	{
		(*pattern_copy) = ft_strndup(pattern, ft_strlen(pattern) - 1);
		repo = "/";
	}
	else if (ft_strstr(pattern, "./") == pattern)
	{
		(*pattern_copy) = ft_strdup(pattern + 2);
		repo = "./";
	}
	else
		(*pattern_copy) = ft_strdup(pattern);
	return (repo);
}

int	find_match(const char *pattern, const char *str)
{
	if (match(pattern, str))
		return (1);
	return (-1);
}
