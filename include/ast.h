/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:44:54 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/05 18:24:21 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "libft.h"
# include "minishell.h"
# include "tokens.h"
# include "redirections.h"
# include "utils.h"
# include <stdbool.h>

typedef struct s_minishell		t_minishell;
typedef struct s_tokens			t_tokens;
typedef struct s_token_list		t_token_list;

typedef enum e_type_ast
{
	AST_AND,
	AST_OR,
	AST_SUBSHELL,
	AST_PIPE,
	AST_CMD
}								t_type_ast;


typedef struct s_ast_value
{
	t_redirection_list			*redirections;
	char						**argv;
	char						*name;
	int							argc;
	pid_t						pid;
	int							fd_in;
	int							fd_out;
	bool						last_cmd;
}								t_ast_value;

typedef struct s_ast
{
	struct s_ast				*left;
	struct s_ast				*right;
	t_ast_value					value;
	t_type_ast					type;
}								t_ast;

int								create_ast(t_minishell *data, t_tokens *tokens);
int								create_ast_value(t_ast_value *value,
									t_token_list **tokens);
t_ast							*create_nodes(t_token_list *tokens);
void							create_nodes_special(t_token_list *tokens,
									t_ast *left, t_ast *ast);
void							free_ast(t_ast **ast);

#endif // AST_H
