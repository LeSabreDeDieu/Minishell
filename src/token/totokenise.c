/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   totokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:31:38 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/13 10:09:15 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"

void	to_tokenise(char *prompt)
{
	t_token_config	*conf;
	char			*save;
	char			*tmp;
	char			char_tmp;

	if (!prompt)
		return ;
	tmp = ft_strtrim(prompt, " ");
	save = tmp;
	conf = get_token_config();
	while (*tmp)
	{
		if (*tmp == ' ')
		{
			tmp++;
			continue ;
		}
		if (*tmp == '\\' && (*tmp + 1 != '\'' && *tmp + 1 != '"'))
		{
			char_tmp = *(tmp + 1);
			add_token(create_token(&char_tmp, TOKEN_WORD));
			tmp += 2;
			continue ;
		}
		tokenise(&tmp, conf);
	}
	free(save);
}
