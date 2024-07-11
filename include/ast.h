/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:44:54 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/11 13:36:31 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_type_redirection
{
	HERE_DOC,
	READ,
	WRITE,
	APPEND
}	t_type_redirection;

typedef struct s_redirection
{
	char					*filename;
	t_type_redirection		flag;
}	t_redirection;

typedef struct s_redirection_list
{
	t_redirection				*redirection;
	struct s_redirection_list	*next;
}	t_redirection_list;

typedef struct s_ast_value
{
	t_redirection_list		*redirections;
	char					**argv;
	char					*name; //argv[0]
	int						argc;
}	t_ast_value;

typedef struct s_ast
{
	struct ast	*left;
	struct ast	*right;
	t_ast_value	value;
}	t_ast;

#endif //AST_H
