/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:27:43 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/19 16:20:36 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "tokens.h"
# include <stdbool.h>
# include <stdlib.h>

// typedef union u_ast_data
// {
// 	t_token			*token;
// 	t_ast_command	*command;
// } 					t_ast_data;

typedef struct s_ast
{
	//t_ast_data		data;
	t_token			*token;
	int				type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_ast_factory
{
	t_ast		*ast;
	bool		instanced;
}				t_ast_factory;

t_ast_factory	*get_ast_factory(void);

t_ast			*create_ast(t_token_list *token);
void			free_ast(t_ast *ast);

void			pre_parse(t_token_list **token);

#endif