/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:42:00 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/21 15:18:41 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "tokens.h"

int	tokenise_quote(t_tokens *tokens, char **str, t_token_type type)
{
	char	*tmp;

	tmp = ft_substr(*str, 0, (ft_strchr(*str + 1,
					tokens->token_config[type][0]) - *str) + 1);
	if (!tmp)
		return (FAILURE);
	add_token(tokens, create_token(tmp, TOKEN_WORD));
	*str += ft_strlen(tmp);
	free(tmp);
	return (SUCCESS);
}
