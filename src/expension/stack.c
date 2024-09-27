/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:29:48 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/27 10:11:33 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stack	*new_stack(char *str)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	new->next = NULL;
	return (new);
}

void	add_stack(t_stack **stack, t_stack *new)
{
	t_stack	*tmp;

	if (!*stack)
	{
		*stack = new;
		return ;
	}
	tmp = *stack;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_stack(t_stack **stack)
{
	t_stack	*tmp;
	t_stack	*current;

	current = *stack;
	while (current)
	{
		tmp = current;
		current = tmp->next;
		free(tmp->str);
		free(tmp);
	}
	*stack = NULL;
}

int	stack_len(t_stack *stack)
{
	t_stack	*tmp;
	int		i;

	tmp = stack;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**stack_to_argv(t_stack *stack)
{
	t_stack	*tmp;
	char	**argv;
	int		i;

	argv = ft_calloc(stack_len(stack) + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	tmp = stack;
	while (tmp)
	{
		if (tmp->str != NULL && ft_strlen(tmp->str) > 0)
		{
			argv[i] = ft_strdup(tmp->str);
			i++;
		}
		tmp = tmp->next;
	}
	free_stack(&stack);
	return (argv);
}
