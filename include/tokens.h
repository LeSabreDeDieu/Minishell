/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:52:56 by gcaptari          #+#    #+#             */
/*   Updated: 2024/06/02 11:42:20 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
#define TOKENS_H
# include <stdbool.h>

typedef enum e_token_type {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_SEQUENCE,
	TOKEN_REDIRECTION,
	TOKEN_SUBSHELL,
	TOKEN_FUNCTION,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_SIMPLE_QUOTE
}			t_token_type;

typedef struct	s_token {
	struct s_token	*next;
	char			*value;
	t_token_type 	type;
}				t_token;

typedef struct s_token_config {
	char *redirection;
	char *sequence;
	char *function;
	char pipe;
	char variable;
	char subshell_start;
	char subshell_end;
	char double_quote;
	char simple_quote;
}				t_token_config;

typedef struct	s_token_factory {
	t_token 	*token;
	t_token_config config;
	bool			instanced;
}				t_token_factory;

t_token_factory	*get_token_factory(void);
t_token_config	*get_token_config(void);

t_token 		*parse_token(char *value);
t_token 		*create_token(char *value, t_token_type type);
t_token 		*add_token(t_token	*token);

#endif