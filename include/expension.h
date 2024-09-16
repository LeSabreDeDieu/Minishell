/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:16:42 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/11 23:36:59 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPENSION_H
# define EXPENSION_H

# include "ast.h"
# include "minishell.h"

typedef struct s_ast_value	t_ast_value;

void	expend_variable(t_ast_value *value, int i, int *j, bool is_quoted);
void	to_dequote(t_ast_value *value);
int		expand_wildcard(const char *pattern, char ***argv, int *argc);
int		expend(t_ast_value *value);

//Utils
void	expend_variable_from_env(t_ast_value *value, int i, int *j);
bool	is_in_dquote(char c, bool is_in_quote);
void	get_pid_as_string(char *pid_str);
bool	wildcard_in_quote(char *str);
int		pos_next_quote(char *str);
char	*get_end(char *str);

#endif