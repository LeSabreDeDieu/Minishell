/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   totokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:03:20 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/14 15:07:50 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	tokenise_prompt(t_tokens *tokens, char *prompt, bool is_and_or)
{
	char	*save;
	char	*tmp;

	if (!prompt || !*prompt)
		return ;
	tmp = ft_strtrim(prompt, " ");
	if (!tmp)
		return ;
	save = tmp;
	while (*tmp)
	{
		if (contain_and_or(tmp))
			return (tokenise_and_or(tokens, &tmp), free(save));
		if (ft_isspace(*tmp))
		{
			tmp++;
			continue ;
		}
		if (tokenise(&tmp, tokens, is_and_or) == FAILURE)
		{
			(free_token(tokens), tokens->first_token = NULL);
			break ;
		}
	}
	free(save);
}

void	to_tokenise(t_minishell *data, char *prompt)
{
	t_tokens	*tokens;

	if (!data->tokens)
	{
		tokens = ft_calloc(1, sizeof(t_tokens));
		if (!tokens)
			return ;
		tokens->first_token = NULL;
		tokens->token_config[0] = "&&";
		tokens->token_config[1] = "||";
		tokens->token_config[2] = "()";
		tokens->token_config[3] = "$";
		tokens->token_config[4] = "|";
		tokens->token_config[5] = "<>";
		tokens->token_config[6] = "\"";
		tokens->token_config[7] = "'";
		data->tokens = tokens;
	}
	else
		tokens = data->tokens;
	tokenise_prompt(tokens, prompt, false);
}
