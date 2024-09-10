/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:16:42 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/10 22:45:52 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPENSION_H
# define EXPENSION_H

# include "ast.h"
# include "minishell.h"

typedef struct s_ast_value	t_ast_value;

void	expend_variable(t_ast_value *value);
void	to_dequote(t_ast_value *value);
void	expand_wildcard(const char *pattern, char ***argv, int *argc);

//Utils
bool	is_in_quote(char c, bool is_in_quote);

#endif