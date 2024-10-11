/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:45:05 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/11 12:39:15 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include <stdbool.h>
# include "minishell.h"

typedef struct s_minishell	t_minishell;

typedef enum e_token_type
{
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SUBSHELL,
	TOKEN_VARIABLE,
	TOKEN_PIPE,
	TOKEN_REDIRECTION,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_SIMPLE_QUOTE,
	TOKEN_WORD
}			t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}					t_token;

typedef struct s_token_list
{
	t_token				*token;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}						t_token_list;

typedef struct s_tokens
{
	t_token_list		*first_token;
	char				*token_config[8];
}						t_tokens;

t_token	*create_token( char *value, t_token_type type );
int		add_token( t_tokens *tokens, t_token *token );

int		tokenise( char **str, t_tokens *tokens, bool and_or );
void	to_tokenise( t_minishell *data, char *prompt );
void	tokenise_prompt( t_tokens *tokens, char *prompt, bool is_and_or );
void	tokenise_and_or( t_tokens *tokens, char **str );

char	*get_word( char **str );

bool	check_valid_token( t_tokens *tokens );

void	free_token( t_tokens *tokens );

int		tokenise_quote(t_tokens *tokens, char **str, t_token_type type);
int		tokenise_subshell(t_tokens *tokens, char **str, t_token_type type);

bool	check_is_in_shell(char *str);
bool	contain_and_or(char *str);
bool	is_space_in_quotes(char *str);

void	token_syntax_error(char *str);
void	token_not_close(char *str);

#endif
