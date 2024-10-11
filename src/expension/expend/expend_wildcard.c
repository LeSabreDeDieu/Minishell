/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:32:37 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/11 08:33:55 by sgabsi           ###   ########.fr       */
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

void	add_wildcard_no_found(t_dlist **wildcard, char *pattern)
{
	char	*tmp;
	t_dlist	*new;

	tmp = ft_strdup(pattern);
	if (tmp == NULL)
		return ;
	new = new_dlist(tmp);
	if (new == NULL)
		return (free(tmp));
	add_dlist(wildcard, new);
	free(tmp);
}

void	do_wildcard(t_dlist **wildcard, char *pattern, DIR *dir)
{
	struct dirent	*entry;
	char			*pattern_copy;
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
		add_wildcard_no_found(wildcard, pattern);
	free(pattern_copy);
}

int	add_matching_files(t_dlist **wildcard, char *pattern)
{
	DIR	*dir;

	dir = opendir(".");
	if (!dir)
		return (FAILURE);
	do_wildcard(wildcard, pattern, dir);
	closedir(dir);
	return (SUCCESS);
}

int	expend_wildcard(t_minishell *shell_data, char *argv)
{
	DIR		*dir;
	int		i;

	i = 0;
	dir = opendir(".");
	if (!dir)
		return (FAILURE);
	if (ft_strchr(argv, '*'))
	{
		if (add_matching_files(&shell_data->stack, argv) == FAILURE)
			return (FAILURE);
	}
	closedir(dir);
	return (SUCCESS);
}
