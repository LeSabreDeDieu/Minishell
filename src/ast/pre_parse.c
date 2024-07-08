/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:35:32 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/08 12:31:08 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

static char	*strjoin_free_word(char **s1, char **s2)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(*s1, " ");
	tmp2 = ft_strjoin(tmp, *s2);
	free(tmp);
	free(*s1);
	free(*s2);
	return (tmp2);
}

static char	*strjoin_free(char **s1, char **s2)
{
	char	*tmp;

	tmp = ft_strjoin(*s1, *s2);
	free(*s1);
	free(*s2);
	return (tmp);
}

#include <stdio.h>

void	pre_parse(t_token_list **token)
{
	t_token_list	*current;

	current = *token;
	while (current)
	{
		if (current->token->type == TOKEN_WORD)
		{
			if (current->next && current->next->token->type == TOKEN_WORD)
			{
				current->token->value = strjoin_free_word(&current->token->value,
						&current->next->token->value);
				free(current->next->token);
				current->next = current->next->next;
				continue;
			}
		}
		if (current->token->type == TOKEN_REDIRECTION)
		{
			if (current->next && current->next->token->type == TOKEN_WORD)
			{
				current->token->value = strjoin_free(&current->token->value,
						&current->next->token->value);
				free(current->next->token);
				current->next = current->next->next;
			}
		}
		current = current->next;
	}
}
