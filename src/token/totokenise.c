/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   totokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:03:20 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/23 14:31:34 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int	tokenise_prompt(t_tokens *tokens, char *prompt, bool is_and_or)
{
	char	*save;
	char	*tmp;
	int		status;

	if (!prompt || !*prompt)
		return (FAILURE);
	tmp = ft_strtrim(prompt, " ");
	if (!tmp)
		return (ENOMEM);
	save = tmp;
	while (*tmp)
	{
		if (contain_and_or(tmp))
			return (tokenise_and_or(tokens, &tmp), free(save), SUCCESS);
		if (ft_isspace(*tmp))
		{
			tmp++;
			continue ;
		}
		status = tokenise(&tmp, tokens, is_and_or);
		if (status == FAILURE || status == ENOENT)
			return (free_token(tokens), tokens->first_token = NULL, status);
	}
	return (free(save), SUCCESS);
}

int	to_tokenise(t_minishell *data, char *prompt)
{
	t_tokens	*tokens;

	if (!data->tokens)
	{
		tokens = ft_calloc(1, sizeof(t_tokens));
		if (!tokens)
			return (ENOMEM);
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
	return (tokenise_prompt(tokens, prompt, false));
}
