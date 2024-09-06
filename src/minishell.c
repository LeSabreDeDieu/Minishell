/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:28:15 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/06 04:58:21 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "minishell.h"
#include "tokens.h"
#include "libft.h"
#include "stdbool.h"

#include "test.h"

static void	usage(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd("What did you do that ? ", 2);
		ft_putendl_fd("Why did you gave to me some arguments ?\n", 2);
	}
}

int	traitement(t_minishell *data, char *prompt)
{
	to_tokenise(data, prompt);
	free(prompt);
	if (!check_valid_token(data->tokens))
		return (ft_putendl_fd("TOKEN ERROR !", 2), false);
	create_ast(data, data->tokens);
	test_execution(data, data->ast);
	free_ast(&data->ast);
	free_token(data->tokens);
	return (0);
}

static char	*minishell(char *envp[])
{
	t_minishell	data;
	char		*line;
	int			dup_test;

	init_signal();
	create_env(envp);
	ft_bzero(&data, sizeof(t_minishell));
	ft_putendl_fd("Welcome to minishell", 1);
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		line = rl_gets();
		g_signal = 0;
		if (!line)
			exit_command(&data, 1, NULL);
		if (!*line)
		{
			free(line);
			continue ;
		}
		init_signal();
		traitement(&data, line);
	}
}

int	main(int argc, char const *argv[], char *envp[])
{
	(void)argv;

	usage(argc);
	minishell(envp);
	return (0);
}

