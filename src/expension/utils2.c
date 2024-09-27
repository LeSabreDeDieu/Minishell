/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:07:10 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/27 12:59:54 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

bool	wildcard_in_quote(char *str)
{
	if (ft_strchr(str, '"') == NULL && ft_strchr(str, '\'') == NULL)
		return (0);
	else if (ft_strchr(str, '"') != NULL)
		return ((ft_strchr(str, '"') < ft_strchr(str, '*') && ft_strchr(str,
					'*') < ft_strchr(ft_strchr(str, '"') + 1, '"')));
	else
		return ((ft_strchr(str, '\'') < ft_strchr(str, '*') && ft_strchr(str,
					'*') < ft_strchr(ft_strchr(str, '\'') + 1, '\'')));
}

static char	**ft_realloc_str_tab(char **str, int size, int j)
{
	char	**new_tab;
	int		i;

	new_tab = ft_calloc(size + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = j;
	while (i < size)
	{
		new_tab[i] = ft_strdup(str[(i - j) + 1]);
		i++;
	}
	free_str_tab(str);
	str = NULL;
	return (new_tab);
}

void	ft_realloc_and_split(t_ast_value *value, int i)
{
	char	**split;
	int		k;

	k = 0;
	split = ft_split(value->argv[i], ' ');
	while (split[k])
	{
		printf ("split[%d] = %s\n", k, split[k]),
		k++;
	}
	value->argc += k - 1;
	value->argv = ft_realloc_str_tab(value->argv, value->argc, k);
	k = 0;
	while (split[k])
	{
		value->argv[k] = ft_strdup(split[k]);
		k++;
	}
	free_str_tab(split);
}

void	wildcard_error_message(const char *pattern)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(" : no matches found: ", 2);
	ft_putendl_fd((char *)pattern, 2);
}

void	dequote_delimiter(t_redirection_list *redir_list)
{
	t_redirection_list	*current;
	char				*filename;

	current = redir_list;
	while (current)
	{
		if (current->redirection.flag == HERE_DOC)
		{
			filename = dequote(current->redirection.filename);
			current->redirection.filename = filename;
		}
		current = current->next;
	}
}
