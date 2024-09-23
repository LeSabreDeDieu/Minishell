/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:29:48 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/20 21:08:00 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

t_wildcard	*new_wildcard(char *str)
{
	t_wildcard	*new;

	new = malloc(sizeof(t_wildcard));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	new->next = NULL;
	return (new);
}

void	add_wildcard(t_wildcard **wildcard, t_wildcard *new)
{
	t_wildcard	*tmp;

	if (!*wildcard)
	{
		*wildcard = new;
		return ;
	}
	tmp = *wildcard;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_wildcard(t_wildcard **wildcard)
{
	t_wildcard	*tmp;
	t_wildcard	*current;

	current = *wildcard;
	while (current)
	{
		tmp = current;
		current = tmp->next;
		free(tmp->str);
		free(tmp);
	}
	*wildcard = NULL;
}

int	wildcard_len(t_wildcard *wildcard)
{
	t_wildcard	*tmp;
	int			i;

	tmp = wildcard;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
