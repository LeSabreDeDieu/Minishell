/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:53:29 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/27 11:23:27 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <unistd.h>

# include "libft.h"

typedef struct s_stack
{
	char			*str;
	struct s_stack	*next;
}					t_stack;

t_stack				*new_stack(char *str);
int					stack_len(t_stack *stack);
void				add_stack(t_stack **stack, t_stack *new_stack);
void				free_stack(t_stack **stack);
char				**stack_to_argv(t_stack **stack);

#endif