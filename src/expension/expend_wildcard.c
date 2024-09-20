/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:32:37 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/20 20:49:42 by sgabsi           ###   ########.fr       */
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

char **struct_to_argv(t_wildcard *wildcard)
{
	t_wildcard	*tmp;
	char		**argv;
	int			i;

	tmp = wildcard;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
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
	argv[i] = NULL;
	free_wildcard(&wildcard);
	return (argv);
}

void	add_matching_files(t_wildcard **wildcard, const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*pattern_copy;
	bool			is_repo;
	char			*tmp;

	dir = opendir(".");
	if (!dir)
		return ;
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
	}
	closedir(dir);
	free(pattern_copy);
}

int	expend_wildcard(char *pattern, char ***argv, int *argc)
{
	t_wildcard		*wildcard;
	DIR				*dir;
	char			*pattern_copy;
	int				i;

	i = 0;
	wildcard = NULL;
	dir = opendir(".");
	if (!dir)
		return (FAILURE);
	pattern_copy = ft_strdup(pattern);
	while (ft_strncmp((*argv)[i], pattern, ft_strlen(pattern)) != 0)
	{
		add_wildcard(&wildcard, new_wildcard((*argv)[i]));
		free((*argv)[i]);
		i++;
	}
	add_matching_files(&wildcard, pattern);
	free((*argv)[i]);
	while ((*argv)[++i])
	{	
		add_wildcard(&wildcard, new_wildcard((*argv)[i]));
		free((*argv)[i]);
	}
	free((*argv));
	closedir(dir);
	free(pattern_copy);
	if (!wildcard)
	{
		wildcard_error_message(pattern);
		return (FAILURE);
	}
	(*argc) = wildcard_len(wildcard);
	(*argv) = struct_to_argv(wildcard);
	return (SUCCESS);
}
