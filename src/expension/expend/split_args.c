/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:50:41 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/17 15:26:22 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

int	add_split_to_stack(t_dlist **stack, char **split)
{
	int		i;
	t_dlist	*new;

	i = 0;
	while (split[i])
	{
		new = new_dlist(split[i]);
		if (new == NULL)
		{
			free_dlist(stack);
			return (free_str_tab(split), FAILURE);
		}
		add_dlist(stack, new);
		++i;
	}
	return (SUCCESS);
}

char	**ft_split_not_in_quote(char *str)
{
	char	**split;
	char	*tmp;
	char	*tmp2;
	size_t	nb_words;
	size_t	i;

	if (str == NULL)
		return (NULL);
	tmp = str;
	nb_words = 1;
	while (*tmp)
	{
		tmp2 = (char *)find_space(tmp);
		if (tmp2 == NULL)
			break ;
		nb_words++;
		tmp = tmp2 + 1;
	}
	split = ft_calloc((nb_words + 1), sizeof(char *));
	if (split == NULL)
		return (NULL);
	tmp = str;
	i = 0;
	while (*tmp && i < nb_words)
	{
		tmp2 = (char *)find_space(tmp);
		if (tmp2 == NULL)
			split[i] = ft_strdup(tmp);
		else
			split[i] = ft_substr(tmp, 0, tmp2 - tmp);
		if (split[i] == NULL)
		{
			free_str_tab(split);
			return (NULL);
		}
		if (tmp2 != NULL)
			tmp = tmp2 + 1;
		else
			tmp = tmp;
		i++;
	}
	split[i] = NULL;
	return (split);
}

void	split_current_stack_element(t_dlist **stack, t_dlist **current)
{
	char	**split;
	t_dlist	*save_next;

	save_next = (*current)->next;
	if ((*current)->prev == NULL)
		*stack = NULL;
	else
		(*current)->prev->next = NULL;
	split = ft_split_not_in_quote((*current)->str);
	if (!split)
		return ;
	free((*current)->str);
	free((*current));
	if (add_split_to_stack(stack, split) == FAILURE)
		return (free_str_tab(split));
	free_str_tab(split);
	(*current) = dlist_last(*stack);
	(*current)->next = save_next;
	if (save_next)
		save_next->prev = (*current);
}

void	handle_stack_splitting(t_dlist **stack, t_dlist **current)
{
	t_dlist	*save_prev;

	if ((*current)->str == NULL || (*current)->str[0] == '\0')
	{
		save_prev = (*current)->prev;
		(*current)->prev->next = (*current)->next;
		if ((*current)->next)
			(*current)->next->prev = (*current)->prev;
		free((*current)->str);
		free(*current);
		*current = save_prev;
		return ;
	}
	split_current_stack_element(stack, current);
}

void	split_stack_elements(t_dlist **stack)
{
	t_dlist	*current;

	current = *stack;
	while (current)
	{
		handle_stack_splitting(stack, &current);
		current = current->next;
	}
}
