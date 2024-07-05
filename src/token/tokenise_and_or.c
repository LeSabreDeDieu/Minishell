/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_and_or.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:34:52 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/20 15:09:33 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "tokens.h"
#include <stdio.h>

int	check_and_or(char *str)
{
	char *and;
	char *or;

	and = ft_strstr(str, "&&");
	or = ft_strstr(str, "||");
	if (or && and && and < or)
		return (1);
	if (or && and && or < and)
		return (2);
	if (and)
		return (1);
	if (or)
		return (2);
	return (0);
}

void	tokenise_and_or(char **str, t_token_config *conf)
{
	char	*tmp;

	tmp = NULL;
	if (check_and_or(*str) == 1)
	{
		tmp = ft_substr(*str, 0, ft_strstr(*str, conf->and) - *str);
		if (!tmp)
			return ;
		if (ft_strchr(tmp, conf->pipe))
			add_token(create_token(tmp, TOKEN_SUBSHELL));
		else
			to_tokenise(tmp, true);
		add_token(create_token("&&", TOKEN_AND));
		*str += ft_strlen(tmp) + 2;
	}
	else if (check_and_or(*str) == 2)
	{
		tmp = ft_substr(*str, 0, ft_strstr(*str, conf->or) - *str);
		printf("tmp = %s\n", tmp);
		if (!tmp)
			return ;
		if (ft_strchr(tmp, conf->pipe))
			add_token(create_token(tmp, TOKEN_SUBSHELL));
		else
		to_tokenise(tmp, true);
		add_token(create_token("||", TOKEN_OR));
		*str += ft_strlen(tmp) + 2;
	}
	if (!tmp)
		free(tmp);
	to_tokenise(*str, true);
}
