/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   totokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:31:38 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/05 16:57:30 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	to_tokenise(char *prompt)
{
	t_token_config	*conf;
	char			*tmp;

	if (!prompt)
		return ;
	tmp = prompt;
	conf = get_token_config();
	while (*tmp)
	{
		if (*tmp == ' ')
		{
			tmp++;
			continue ;
		}
		tokenise(&tmp, conf);
	}
}
