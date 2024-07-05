/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:31:50 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/05 13:13:32 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

// static void	print_token(void)
// {
// 	t_token_factory	*fac;
// 	t_token			*current;
// 	const char		*token_names[8] = {"WORD", "VARIABLE", "PIPE",
// 		"REDIRECTION", "SUBSHELL", "DOUBLE_QUOTE",
// 		"SIMPLE_QUOTE"};

// 	fac = get_token_factory();
// 	if (!fac)
// 		return ;
// 	current = fac->token;
// 	printf("Tokenisation : \n");
// 	while (current)
// 	{
// 		printf("[%s] => #%s#\n", token_names[current->type], current->value);
// 		if (!current->next)
// 			break ;
// 		current = current->next;
// 	}
// }

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	char *argv_c[3];
	// char *line;

	if (!test_env_config())
		return (0);
	create_env(envp); 
	print_env();
	unset_command(argc, argv);
	ft_putstr_fd("\n--------------------------------------------------------\n", 1);
	argv_c[1] = "cd";
	argv_c[2] = "..";
	cd_command(3, argv_c);
	env_command(0, NULL);
	free_env();
	// while (true)
	// {
	// 	line = rl_gets();
	// 	if (!line)
	// 	{
	// 		free_env();
	// 		return (0);
	// 	}
	// 	to_tokenise(argv[1]);
	// 	print_token();
	// 		printf("%s\n", line);
	// 	}
	return (0);
}
