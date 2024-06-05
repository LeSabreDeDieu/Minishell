/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:01:22 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/03 14:01:22 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# include <stdbool.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_VARIABLE,
	TOKEN_PIPE,
	TOKEN_REDIRECTION,
	TOKEN_SUBSHELL,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_SIMPLE_QUOTE
}			t_token_type;

typedef struct s_token
{
	struct s_token	*next;
	char			*value;
	t_token_type	type;
}					t_token;

typedef struct s_token_config
{
	char	*redirection;
	char	pipe;
	char	variable;
	char	subshell_start;
	char	subshell_end;
	char	double_quote;
	char	simple_quote;
}			t_token_config;

typedef struct s_token_factory
{
	t_token			*token;
	t_token_config	config;
	bool			instanced;
}					t_token_factory;

t_token_factory	*get_token_factory(void);
t_token_config	*get_token_config(void);

t_token			*parse_token(char *value);
t_token			*create_token(char *value, t_token_type type);
void			add_token(t_token *token);

void			tokenise(char **str, t_token_config *conf);
void			to_tokenise(char *prompt);

char			*get_word(char **str);

void			free_token(void);

#endif

// < in cat | grep {word} | ls >> out 

// [redirection]=>"<" [word]=>"in" [word]=>cat [pipe] [word]=>"grep" [word]=>args [pipe] [word]=>"ls" [redirection]=>">>" [word]=>"out"
/*

<	=	REDIRECTION_IN
<<	=	HERE_DOC

>	=	REDIRCTION_OUT
>>	=	REDIRCTION_OUT_APPEND

*/