/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:50:41 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/22 13:53:20 by gcaptari         ###   ########.fr       */
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
	if((*current))
		(*current)->next = save_next;
	if (save_next)
		save_next->prev = (*current);
}

void	handle_stack_splitting(t_dlist **stack, t_dlist **current)
{


	split_current_stack_element(stack, current);
}

void	split_stack_elements(t_dlist **stack)
{
	t_dlist	*current;
	t_dlist	*save_prev;
	t_dlist	*tmp;

	current = *stack;
	if (current && ((current)->str == NULL))
	{
		save_prev = (current)->prev;
		if(save_prev)
			save_prev->next = (current)->next;
		if ((current)->next)
			(current)->next->prev = save_prev;
		tmp = current;
		if(save_prev)
			current = save_prev;
		else
		{
			current = tmp->next;
			*stack = current;
		}
	}
	while (current)
	{
		handle_stack_splitting(stack, &current);
		if(current)
			current = current->next;
	}

	current = *stack;
	while (current)
	{
		printf("stack => %s\n", current->str);
		if(current)
			current = current->next;
	}

}
