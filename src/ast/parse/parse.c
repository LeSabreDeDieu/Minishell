/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/06/03 09:34:55 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/03 09:34:55 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokens.h"


void	parse_token(char *prompt)
{
	t_token_config *conf;
	t_token *token_tmp;
	char *tmp;
	char *p;

	if (!prompt)
		return ;
	tmp = prompt;
	conf = get_token_config();
	while (*tmp)
	{
		if (*tmp == conf->double_quote)
		{
			token_tmp = create_token("\"", TOKEN_DOUBLE_QUOTE);
			if (!token_tmp)
				return ; // free all token
		}
		else if (*tmp == conf->simple_quote)
		{
			token_tmp = create_token("\'", TOKEN_SIMPLE_QUOTE);
			if (!token_tmp)
				return ; // free all token
		}
		else if (*tmp == conf->pipe)
		{
			token_tmp = create_token("|", TOKEN_PIPE);
			if (!token_tmp)
				return ; // free all token
		}
		else if (*tmp == conf->redirection[0])
		{
			p = "<";
			if (*(tmp + 1) == conf->redirection[0])
			{
				tmp++;
				p = "<<";
			}
			token_tmp = create_token(p, TOKEN_REDIRECTION);
			if (!token_tmp)
				return ; // free all token
		}
		else if (*tmp == conf->redirection[1])
		{
			p = ">";
			if (*(tmp + 1) == conf->redirection[1])
			{
				tmp++;
				p = ">>";
			}
			token_tmp = create_token(p, TOKEN_REDIRECTION);
			if (!token_tmp)
				return ; // free all token
		}
		else if (*tmp == conf->subshell_start)
		{
			token_tmp = create_token("(", TOKEN_SUBSHELL);
			if (!token_tmp)
				return ; // free all token
		}
		else if (*tmp == conf->subshell_end)
		{
			token_tmp = create_token(")", TOKEN_SUBSHELL);
			if (!token_tmp)
				return ; // free all token
		}
		else if (*tmp == conf->variable)
		{
			token_tmp = create_token("$", TOKEN_VARIABLE);
			if (!token_tmp)
				return ; // free all token
		}
		else
		{
			token_tmp = create_token("", TOKEN_WORD); //TODO : fonction to get a single word
			if (!token_tmp)
				return ; // free all token
		}
	}
}
