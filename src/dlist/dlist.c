/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:29:48 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/04 16:57:47 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"
#include "utils.h"

t_dlist	*new_dlist(char *str)
{
	t_dlist	*new_dlist;

	new_dlist = ft_calloc(1, sizeof(t_dlist));
	if (!new_dlist)
		return (NULL);
	new_dlist->str = ft_strdup(str);
	if (!new_dlist->str)
		return (free(new_dlist), NULL);
	new_dlist->next = NULL;
	new_dlist->prev = NULL;
	return (new_dlist);
}

void	add_dlist(t_dlist **dlist, t_dlist *new_dlist)
{
	t_dlist	*tmp;

	if (!new_dlist)
		return ;
	if (!*dlist)
	{
		*dlist = new_dlist;
		return ;
	}
	tmp = *dlist;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_dlist;
	new_dlist->prev = tmp;
}

void	free_dlist(t_dlist **dlist)
{
	t_dlist	*tmp;
	t_dlist	*current;

	current = *dlist;
	while (current)
	{
		tmp = current;
		current = tmp->next;
		free(tmp->str);
		free(tmp);
	}
	*dlist = NULL;
}

int	dlist_len(t_dlist *dlist)
{
	t_dlist	*tmp;
	int		i;

	tmp = dlist;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**dlist_to_argv(t_dlist **dlist)
{
	t_dlist	*tmp;
	char	**argv;
	int		i;

	argv = ft_calloc(dlist_len(*dlist) + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	tmp = *dlist;
	while (tmp)
	{
		if (tmp->str != NULL && ft_strlen(tmp->str) > 0)
		{
			argv[i] = ft_strdup(tmp->str);
			if (!argv[i])
				return (free_str_tab(argv), NULL);
			i++;
		}
		tmp = tmp->next;
	}
	free_dlist(dlist);
	*dlist = NULL;
	return (argv);
}
