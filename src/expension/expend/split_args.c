/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:50:41 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/22 15:15:06 by sgabsi           ###   ########.fr       */
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
	if (*current)
		(*current)->next = save_next;
	if (save_next)
		save_next->prev = *current;
}

void	clean_split_stack(t_dlist **stack)
{
	t_dlist	*current;
	t_dlist	*tmp;

	current = *stack;
	while (current)
	{
		if (current->str == NULL || current->str[0] == '\0')
		{
			free(current->str);
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			tmp = current;
			current = current->next;
			free(tmp);
		}
		else
			current = current->next;
	}
}

void	split_stack_elements(t_dlist **stack)
{
	t_dlist	*current;

	current = *stack;
	while (current && (current->str == NULL || current->str[0] == '\0')
		&& current->next)
	{
		*stack = current->next;
		(*stack)->prev = NULL;
		free(current->str);
		free(current);
		current = *stack;
	}
	while (current)
	{
		split_current_stack_element(stack, &current);
		if (current)
			current = current->next;
	}
	clean_split_stack(stack);
}
