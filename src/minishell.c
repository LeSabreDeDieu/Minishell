/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:28:15 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/16 16:47:58 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "libft.h"
#include "minishell.h"
#include "stdbool.h"
#include "test.h"
#include "tokens.h"
#include <limits.h>

static void	usage(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd("What did you do that ? ", 2);
		ft_putstr_fd("Why did you gave to me some arguments ?\n\n", 2);
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
	free_token(data->tokens);
	free_ast(&data->ast);
	return (0);
}

static void	init_minishell(t_minishell *data, char **envp)
{
	create_env(envp);
	if (!envp[0])
		set_env_from_void();
	add_shlvl();
	ft_bzero(data, sizeof(t_minishell));
	data->data.username = getenv("PATH");
	printf("Welcome %s\n", data->data.username);
}

static char	*minishell(char *envp[])
{
	t_minishell	data;
	char		*line;

	init_minishell(&data, envp);
	ft_putendl_fd("Welcome to minishell", 1);
	while (true)
	{
		line = rl_gets();
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
		traitement(&data, line);
	}
}

int	main(int argc, char const *argv[], char *envp[])
{
	(void)argv;
	printf("\033]0;SanicShell\007");
	usage(argc);
	minishell(envp);
	return (0);
}
