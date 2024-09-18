/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:28:15 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/18 17:53:34 by sgabsi           ###   ########.fr       */
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
	free_token(data->tokens);
	free_ast(&data->ast);
	return (0);
}

static void	init_minishell(t_minishell *data, char **envp)
{
	create_env(envp);
	init_signal();
	if (!envp[0])
		set_env_from_void();
	add_shlvl();
	ft_bzero(data, sizeof(t_minishell));
	data->data.username = get_uname();
}

static void	minishell(char *envp[])
{
	t_minishell	data;
	char		*line;

	init_minishell(&data, envp);
	read_history_from_file();
	print_welcome();
	while (true)
	{
		line = rl_gets(create_display(&data));
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			continue ;
		}
		else if (g_signal == SIGQUIT)
			g_signal = 0;
		else if (!line)
			exit_command(&data, 1, NULL);
		if (!*line)
		{
			free(line);
			continue ;
		}
		traitement(&data, line);
		ft_putstr_fd("\n", 1);
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
