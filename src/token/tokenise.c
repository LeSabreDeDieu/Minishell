/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:01:24 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/22 14:17:35 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "tokens.h"

static int	tokenise_word(t_tokens *tokens, char **str)
{
	char	*tmp;
	int		status;

	tmp = get_word(str);
	if (!tmp)
		return (FAILURE);
	status = add_token(tokens, create_token(tmp, TOKEN_WORD));
	free(tmp);
	return (status);
}

static int	tokenise_redirect_char(t_tokens *tokens,
									char **str, t_token_type type)
{
	char	tmp[3];

	ft_bzero(tmp, sizeof(tmp));
	if (**str == tokens->token_config[type][0])
	{
		tmp[0] = tokens->token_config[type][0];
		if (*(*str + 1) == tokens->token_config[type][0])
			tmp[1] = tokens->token_config[type][0];
	}
	else if (**str == tokens->token_config[type][1])
	{
		tmp[0] = tokens->token_config[type][1];
		if (*(*str + 1) == tokens->token_config[type][1])
			tmp[1] = tokens->token_config[type][1];
	}
	*str += 1;
	if (tmp[1])
		*str += 1;
	return (add_token(tokens, create_token(tmp, type)));
}

int	tokenise(char **str, t_tokens *tokens, bool is_and_or)
{
	int	status;

	if (**str == tokens->token_config[TOKEN_DOUBLE_QUOTE][0])
		status = tokenise_quote(tokens, str, TOKEN_DOUBLE_QUOTE);
	else if (**str == tokens->token_config[TOKEN_SIMPLE_QUOTE][0])
		status = tokenise_quote(tokens, str, TOKEN_SIMPLE_QUOTE);
	else if (**str == tokens->token_config[TOKEN_SUBSHELL][0])
		status = tokenise_subshell(tokens, str, TOKEN_SUBSHELL);
	else if (is_and_or && ft_strchr(*str, '|') && ft_strstr(*str, "||") == NULL)
	{
		status = add_token(tokens, create_token(*str, TOKEN_SUBSHELL));
		*str += ft_strlen(*str);
	}
	else if (**str == tokens->token_config[TOKEN_PIPE][0])
	{
		status = add_token(tokens, create_token("|", TOKEN_PIPE));
		++(*str);
	}
	else if (**str == tokens->token_config[TOKEN_REDIRECTION][0]
			|| **str == tokens->token_config[TOKEN_REDIRECTION][1])
		status = tokenise_redirect_char(tokens, str, TOKEN_REDIRECTION);
	else if (**str == tokens->token_config[TOKEN_VARIABLE][0])
	{
		status = add_token(tokens, create_token("$", TOKEN_WORD));
		++(*str);
	}
	else
	{
		status = tokenise_word(tokens, str);
		++(*str);
	}
	return (status);
}
