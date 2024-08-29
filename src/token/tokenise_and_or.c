/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_and_or.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:14:53 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/21 13:36:05 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include "tokens.h"

static int	check_and_or(char *str)
{
	char	*and;
	char	*or;

	and = ft_strstr(str, "&&");
	or = ft_strstr(str, "||");
	if (or && and && and < or)
		return (TOKEN_AND);
	if (or && and && or < and)
		return (TOKEN_OR);
	if (and)
		return (TOKEN_AND);
	if (or)
		return (TOKEN_OR);
	return (FAILURE);
}

static int	tokenise_or_and(t_tokens *tokens,
							char **str,
							t_token_type type)
{
	char	*tmp;

	if ((int) type == FAILURE)
		return (SUCCESS);
	tmp = ft_substr(*str, 0, ft_strstr(*str,
				tokens->token_config[type]) - *str);
	if (!tmp)
		return (FAILURE);
	if (ft_strchr(tmp, tokens->token_config[TOKEN_PIPE][0]))
		add_token(tokens, create_token(tmp, TOKEN_SUBSHELL));
	else
		tokenise_prompt(tokens, tmp, true);
	add_token(tokens, create_token(tokens->token_config[type], type));
	*str += ft_strlen(tmp) + 2;
	if (tmp)
		free(tmp);
	return (SUCCESS);
}

void	tokenise_and_or(t_tokens *tokens, char **str)
{
	if (tokenise_or_and(tokens, str, check_and_or(*str)) == FAILURE)
		return ;
	tokenise_prompt(tokens, *str, true);
}
