/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   totokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:03:20 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/30 10:51:15 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "minishell.h"
#include "libft.h"

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
		{
			tokenise_and_or(tokens, &tmp);
			free(save);
			check_valid_token(tokens);
			return ;
		}
		while (*tmp == ' ')
			tmp++;
		tokenise(&tmp, tokens, is_and_or);
	}
	free(save);
	check_valid_token(tokens);
	return ;
}

void	to_tokenise(t_minishell *data, char *prompt)
{
	t_tokens	*tokens;

	if (!data->tokens)
	{
		tokens = ft_calloc(1, sizeof(t_tokens));
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
