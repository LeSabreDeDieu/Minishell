/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:44:54 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/19 14:41:55 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <stdbool.h>

# include "libft.h"
# include "tokens.h"
# include "utils.h"
# include "minishell.h"

typedef struct s_minishell	t_minishell;
typedef struct s_tokens		t_tokens;
typedef struct s_token_list	t_token_list;

typedef enum e_type_ast
{
	AST_AND = 1,
	AST_OR,
	AST_SUBSHELL,
	AST_PIPE,
	AST_CMD
}	t_type_ast;

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
	t_redirection				redirection;
	struct s_redirection_list	*next;
}	t_redirection_list;

typedef struct s_ast_value
{
	t_redirection_list		*redirections;
	char					**argv;
	char					*name; //argv[0] or [&& or || or |]
	int						argc;
}	t_ast_value;

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	t_ast_value		value;
	t_type_ast		type;
}	t_ast;

int	create_ast(t_minishell *data, t_tokens *tokens);
int	create_ast_value(t_ast_value *value, t_token_list **tokens);

#endif //AST_H
