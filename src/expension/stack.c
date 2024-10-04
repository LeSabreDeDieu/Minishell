/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:29:48 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/03 16:04:50 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "minishell.h"

t_stack	*new_stack(char *str)
{
	t_stack	*new;

	new = ft_calloc(1, sizeof(t_stack));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!new->str)
		return (free(new), NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_stack(t_stack **stack, t_stack *new)
{
	t_stack	*tmp;

	if (!new)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	tmp = *stack;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
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

char	**stack_to_argv(t_stack **stack)
{
	t_stack	*tmp;
	char	**argv;
	int		i;

	argv = ft_calloc(stack_len(*stack) + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	tmp = *stack;
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
	free_stack(stack);
	*stack = NULL;
	return (argv);
}
