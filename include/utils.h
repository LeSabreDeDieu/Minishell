/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:45:10 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/30 10:52:26 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
typedef struct s_minishell			t_minishell;
void	free_str_tab(char **tabs);
void	free_env(void);
void	free_minishell(t_minishell *minishell, int action);

typedef enum e_error
{
	FAILURE = -1,
	SUCCESS
}	t_error;

enum e_free {
	FREE_AST = 0,
	FREE_ENV = 1,
	FREE_PATH = 1 << 1,
	FREE_UNAME = 1 << 2,
	FREE_PIPE = 1 << 3,
	FREE_FD = 1 << 4,
	FREE_SIGNAL = 1 << 5
};

#endif
