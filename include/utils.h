/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:45:10 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/14 14:44:13 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
typedef struct s_minishell			t_minishell;
void	free_str_tab(char **tabs);
void	free_env(void);
void	free_on_children(t_minishell *minishell);

typedef enum e_error
{
	FAILURE = -1,
	SUCCESS
}	t_error;

#endif
