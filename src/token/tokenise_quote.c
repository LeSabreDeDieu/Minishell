/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:42:00 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/17 15:30:14 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

char	*getlastquote(char *str, char c, char evode)
{
	char	*tmp;
	size_t	nb_quote;

	nb_quote = 0;
	tmp = str;
	while (*tmp)
	{
		if (nb_quote == 0 && *tmp == c)
			++nb_quote;
		else if (nb_quote == 1 && *tmp == c)
			--nb_quote;
		if ((*tmp == ' ' || *tmp == evode) && nb_quote == 0)
			break ;
		tmp++;
	}
	return (tmp);
}

bool	is_quote_closed(char *str, char c, char evode)
{
	size_t	nb_quote;
	char	*tmp;

	nb_quote = 0;
	tmp = str;
	while (*tmp)
	{
		if (nb_quote == 0 && *tmp == c)
			++nb_quote;
		else if (nb_quote == 1 && *tmp == c)
			--nb_quote;
		if ((*tmp == ' ' || *tmp == evode) && nb_quote == 0)
			break ;
		tmp++;
	}
	if (nb_quote == 0)
		return (true);
	return (false);
}

int	tokenise_quote(t_tokens *tokens, char **str, t_token_type type)
{
	char	*tmp;
	int		evode;

	if (type == TOKEN_DOUBLE_QUOTE)
		evode = type + 1;
	else
		evode = type - 1;
	tmp = get_word(str);
	if (!tmp)
		return (FAILURE);
	if (is_quote_closed(tmp, tokens->token_config[type][0],
		tokens->token_config[evode][0]) == false)
		return (free(tmp), error_message("quote not closed"), FAILURE);
	add_token(tokens, create_token(tmp, TOKEN_WORD));
	free(tmp);
	return (SUCCESS);
}
