/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   totokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:40:56 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/20 15:25:02 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "env.h"
#include "builtins.h"
#include "libft.h"
#include <stdio.h>

static	bool	check_is_in_shell(char *str)
{
	char	*search;
	char	*and;
	char	*or;

	search = ft_strstr(str, "(");
	if (!search)
		return (1);
	and = ft_strstr(str, "&&");
	or = ft_strstr(str, "||");
	if (and && and < search)
		return (1);
	if (or && or < search)
		return (1);
	search = ft_strstr(str, "\"");
	if (!search)
		return (1);
	if (and && and < search)
		return (1);
	if (or && or < search)
		return (1);
	search = ft_strstr(str, "\'");
	if (!search)
		return (1);
	if (and && and < search)
		return (1);
	if (or && or < search)
		return (1);
	return (0);
}

static bool	contain_and_or(char *str)
{
	return (*str != '(' && *str != '"' && *str != '\'' && check_is_in_shell(str)
		&& (ft_strstr(str, "&&") != NULL || ft_strstr(str, "||") != NULL));
}

void	to_tokenise(char *prompt, bool is_and_or)
{
	t_token_config	*conf;
	char			*save;
	char			*tmp;

	if (!prompt || !*prompt)
		return ;
	tmp = ft_strtrim(prompt, " ");
	if (!tmp)
		return ;
	save = tmp;
	conf = get_token_config();
	while (*tmp)
	{
		if (contain_and_or(tmp))
		{
			tokenise_and_or(&tmp, conf);
			free(save);
			// if (!check_valid_token())
			// {
			// 	printf("minishell: lexical error\n");
			// 	free_token();
			// 	return ;
			// }
			return ;
		}
		if (*tmp == ' ')
		{
			tmp++;
			continue ;
		}
		tokenise(&tmp, conf, is_and_or);
	}
	free(save);
	// if (!check_valid_token())
	// {
	// 	printf("minishell: lexical error\n");
	// 	free_token();
	// 	return ;
	// }
	return ;
}
