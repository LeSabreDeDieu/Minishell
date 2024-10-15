/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_and_or.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:14:53 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/15 16:17:54 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

static int	check_and_or(char *str)
{
	char	*and;
	char	*or ;

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

bool	is_pipe_valid(const char *input, int index)
{
	if (!input || input[index] != '|'
		|| (input[index] == '|' && input[index + 1] == '|'))
		return (false);
	return (!is_in_quotes(input, index) && !is_in_subshell(input, index));
}

static int	tokenise_or_and(t_tokens *tokens, char **str, t_token_type type)
{
	char	*tmp;

	if ((int)type == FAILURE)
		return (SUCCESS);
	tmp = ft_substr(*str, 0, find_operators(*str) - *str);
	printf("tmp = %s, find op = %s\n", tmp, find_operators(*str));
	if (!tmp)
		return (FAILURE);
	if (ft_strrchr(tmp, '|') && is_pipe_valid(tmp, ft_strrchr(tmp, '|') - tmp))
	{
		add_token(tokens, create_token(tmp, TOKEN_SUBSHELL));
	}
	else
		tokenise_prompt(tokens, tmp, true);
	add_token(tokens, create_token(tokens->token_config[type], type));
	*str += (find_operators(*str) - *str) + 2;
	if (tmp)
		free(tmp);
	return (SUCCESS);
}

void	tokenise_and_or(t_tokens *tokens, char **str)
{
	const char	*or_and = find_operators(*str);

	if (tokenise_or_and(tokens, str, check_and_or((char *)or_and)) == FAILURE)
		return ;
	tokenise_prompt(tokens, *str, true);
}
