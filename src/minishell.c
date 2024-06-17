/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:31:50 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/17 17:57:08 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

static void	print_token(void)
{
	t_token_factory	*fac;
	t_token			*current;
	const char		*token_names[9] = {"AND", "OR", "SUBSHELL", "WORD",
		"VARIABLE", "PIPE", "REDIRECTION", "DOUBLE_QUOTE",
		"SIMPLE_QUOTE"};

	fac = get_token_factory();
	if (!fac)
		return ;
	current = fac->token;
	printf("Tokenisation : \n");
	while (current)
	{
		printf("[%s] => %%%s%%\n", token_names[current->type], current->value);
		if (!current->next)
			break ;
		current = current->next;
	}
	free_token();
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	(void)argc;
	(void)argv;
	if (!test_env_config())
		return (0);
	create_env(envp);
	// print_env();
	while (true)
	{
		line = rl_gets();
		if (!line)
		{
			free_env();
			free_token();
			return (0);
		}
		to_tokenise(line);
		print_token();
	}
	return (0);
}
