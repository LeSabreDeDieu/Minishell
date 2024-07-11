/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:29:33 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/10 17:25:50 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_tokens *tokens)
{
	t_token_list	*current;
	const char		*token_names[9] = {"AND", "OR", "SUBSHELL",
		"VARIABLES", "PIPE", "REDIRECTION", "DOUBLE_QUOTE",
		"SIMPLE_QUOTE", "WORD"};

	if (tokens->first_token == NULL)
		return ;
	current = tokens->first_token;
	printf("Tokenisation : \n");
	while (current)
	{
		printf("[%s] => %%%s%%\n", token_names[current->token->type],
			current->token->value);
		current = current->next;
	}
}
