/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:50:41 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/04 16:09:54 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

void	add_split_to_stack(t_stack **stack, char **split)
{
	int		i;
	t_stack	*new;

	i = 0;
	while (split[i])
	{
		new = new_stack(split[i]);
		if (!new)
		{
			free_stack(stack);
			return (free_str_tab(split));
		}
		add_stack(stack, new);
		++i;
	}
}

void	split_current_stack_element(t_stack **stack, t_stack **current)
{
	char	**split;
	t_stack	*save_next;

	save_next = (*current)->next;
	if ((*current)->prev == NULL)
		*stack = NULL;
	else
		(*current)->prev->next = NULL;
	split = ft_split((*current)->str, ' ');
	if (!split)
		return ;
	free((*current)->str);
	free((*current));
	add_split_to_stack(stack, split);
	free_str_tab(split);
	(*current) = stack_last(*stack);
	(*current)->next = save_next;
	if (save_next)
		save_next->prev = (*current);
}

void	handle_stack_splitting(t_stack **stack, t_stack **current)
{
	t_stack	*save_prev;

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
	if (ft_strchr((*current)->str, ' ') && !char_in_quote((*current)->str, ' '))
		split_current_stack_element(stack, current);
}

void	split_stack_elements(t_stack **stack)
{
	t_stack	*current;

	current = *stack;
	while (current)
	{
		handle_stack_splitting(stack, &current);
		current = current->next;
	}
}
