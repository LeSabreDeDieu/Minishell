/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:45:10 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/04 16:58:40 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdbool.h>
# include <stdio.h>

typedef struct s_minishell	t_minishell;
typedef struct s_ast_value	t_ast_value;

typedef enum e_error
{
	FAILURE = -1,
	SUCCESS,
	LOOP
}				t_error;

enum			e_free
{
	FREE_AST = 1 << 0,
	FREE_ENV = 1 << 1,
	FREE_PATH = 1 << 2,
	FREE_UNAME = 1 << 3,
	FREE_HOME = 1 << 4,
	FREE_PIPE = 1 << 5,
	FREE_FD = 1 << 6,
	FREE_SIGNAL = 1 << 7,
	FREE_TOKEN = 1 << 8,
	FREE_ALL = FREE_AST | FREE_ENV | FREE_PATH | FREE_UNAME | FREE_HOME \
				| FREE_PIPE | FREE_FD | FREE_SIGNAL | FREE_TOKEN
};

void	free_str_tab(char **tabs);
void	free_env(void);
void	free_minishell(t_minishell *minishell, int action);
void	wait_process(t_minishell *data, t_ast_value *value, bool is_pipeline);

#endif
