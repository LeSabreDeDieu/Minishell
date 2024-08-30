/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:28:15 by sgabsi            #+#    #+#             */
/*   Updated: 2024/08/30 10:55:45 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "minishell.h"
#include "tokens.h"
#include "libft.h"
#include "stdbool.h"

#include "test.h"

int	minishell(t_minishell *data, char *prompt)
{
	to_tokenise(data, prompt);
	free(prompt);
	//print_token(data->tokens);
	if (!check_valid_token(data->tokens))
		return (ft_putendl_fd("TOKEN ERROR !", 2), false);
	create_ast(data, data->tokens);
	test_execution(data, data->ast, false);
	//print_ast(data->ast);
	free_ast(&data->ast);
	free_token(data->tokens);
	return (0);
}

int	main(int argc, char const *argv[], char *envp[])
{
	char		*line;
	t_minishell	data;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("What did you do that ? ", 2);
		ft_putstr_fd("why did you gave to me some arguments ?\n", 2);
	}
	ft_bzero(&data, sizeof(t_minishell));
	create_env(envp);
	ft_putendl_fd("Welcome to minishell", 1);
	while (true)
	{
		line = rl_gets();
		printf("%p\n", line);
		if (!line)
		{
			free_env();
			free_ast(&data.ast);
			free_token(data.tokens);
			free(data.tokens);
			exit(0);
		}
		if (!*line)
		{
			free(line);
			continue ;
		}
		minishell(&data, line);
	}
	return (0);
}

