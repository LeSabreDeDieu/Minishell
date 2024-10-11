/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:59:22 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/11 08:35:59 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

static void	add_all(t_dlist **wildcard, char *pattern, struct dirent *entry)
{
	char	*tmp;
	t_dlist	*new;

	if (pattern[0] != '.' && entry->d_name[0] != '.')
	{
		tmp = ft_strdup(entry->d_name);
		if (tmp == NULL)
			return ;
		new = new_dlist(tmp);
		if (new == NULL)
			return (free(tmp));
		add_dlist(wildcard, new);
		free(tmp);
	}
	else if (pattern[0] == '.' && entry->d_name[0] == '.')
	{
		tmp = ft_strdup(entry->d_name);
		if (tmp == NULL)
			return ;
		new = new_dlist(tmp);
		if (new == NULL)
			return (free(tmp));
		add_dlist(wildcard, new);
		free(tmp);
	}
}

static void	add_repo(t_dlist **wildcard, char *pattern, struct dirent *entry,
		char *repo)
{
	char	*tmp;
	t_dlist	*new;

	if (pattern[0] != '.' && entry->d_name[0] != '.' && entry->d_type == 4)
	{
		tmp = ft_strjoin(entry->d_name, repo);
		if (tmp == NULL)
			return ;
		new = new_dlist(tmp);
		if (new == NULL)
			return (free(tmp));
		add_dlist(wildcard, new);
		free(tmp);
	}
	else if (pattern[0] == '.' && entry->d_name[0] == '.' && entry->d_type == 4)
	{
		tmp = ft_strjoin(entry->d_name, repo);
		if (tmp == NULL)
			return ;
		new = new_dlist(tmp);
		if (new == NULL)
			return (free(tmp));
		add_dlist(wildcard, new);
		free(tmp);
	}
}

void	add_file_wildcard(t_dlist **wildcard, char *pattern,
		struct dirent *entry, char *repo)
{
	char	*tmp;
	t_dlist	*new;

	if (repo == NULL)
		add_all(wildcard, pattern, entry);
	else if (ft_strnstr(repo, "/", 1) != NULL)
		add_repo(wildcard, pattern, entry, repo);
	else if (ft_strstr(repo, "./") != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			tmp = ft_strjoin(repo, entry->d_name);
			if (tmp == NULL)
				return ;
			new = new_dlist(tmp);
			if (new == NULL)
				return (free(tmp));
			add_dlist(wildcard, new);
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
		if ((*pattern_copy) == NULL)
			return (NULL);
		repo = "/";
	}
	else if (ft_strstr(pattern, "./") == pattern)
	{
		(*pattern_copy) = ft_strdup(pattern + 2);
		if ((*pattern_copy) == NULL)
			return (NULL);
		repo = "./";
	}
	else
	{
		(*pattern_copy) = ft_strdup(pattern);
		if ((*pattern_copy) == NULL)
			return (NULL);
	}
	return (repo);
}

int	find_match(const char *pattern, const char *str)
{
	if (match(pattern, str))
		return (1);
	return (-1);
}
