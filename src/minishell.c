/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:28:15 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/18 10:41:13 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "here_doc.h"
#include "libft.h"
#include "minishell.h"
#include "ms_signal.h"
#include "stdbool.h"
#include "tokens.h"
#include <limits.h>

static void	usage(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd("What did you do that ? ", STDERR_FILENO);
		ft_putendl_fd("Why did you gave to me some arguments ?\n",
			STDERR_FILENO);
	}
}

int	traitement(t_minishell *data, char *prompt)
{
	int	itter_heredoc;

	to_tokenise(data, prompt);
	if (!data->tokens || !data->tokens->first_token)
		return (FAILURE);
	free(prompt);
	if (!check_valid_token(data->tokens))
		return (free_token(data->tokens), ENOENT);
	if (create_ast(data, data->tokens) == FAILURE)
	{
		free_minishell(data, FREE_AST | FREE_TOKEN);
		return (ENOMEM);
	}
	itter_heredoc = -1;
	if (expend_and_dequote(data, data->ast) == FAILURE)
	{
		free_minishell(data, FREE_AST | FREE_TOKEN);
		return (ENOMEM);
	}
	if (open_all_here_doc(data, data->ast, &itter_heredoc) != FAILURE)
		execute_on_ast(data, data->ast);
	ast_unlink_heredoc(data->ast);
	free_minishell(data, FREE_AST | FREE_TOKEN);
	return (data->current_status);
}

static void	init_minishell(t_minishell *data, char **envp)
{
	create_env(envp);
	init_signal();
	if (!envp[0])
		set_env_from_void();
	add_shlvl();
	ft_bzero(data, sizeof(t_minishell));
	data->current_status = 0;
	data->data.username = get_uname();
	if (!get_env("PATH"))
		data->data.path = get_path();
	else
		data->data.path = NULL;
	data->data.home = ft_strjoin("/home/", data->data.username);
	data->is_here_doc = false;
}

static void	minishell(char *envp[])
{
	t_minishell	data;
	char		*line;

	init_minishell(&data, envp);
	read_history_from_file(&data.data);
	print_welcome();
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		line = rl_gets(&data.data, create_display(&data));
		if (g_signal == SIGINT)
			g_signal = 0;
		else if (g_signal == SIGQUIT)
			g_signal = 0;
		if (!line)
			exit_command(&data, 1, NULL);
		g_signal = 0;
		if (!*line)
		{
			free(line);
			continue ;
		}
		traitement(&data, line);
		init_signal();
	}
}

int	main(int argc, char const *argv[], char *envp[])
{
	(void)argv;
	ft_putstr_fd("\033[6 q\007\033[?12h\007", STDOUT_FILENO);
	ft_putstr_fd("\033]2;SanicShell\007", STDOUT_FILENO);
	usage(argc);
	minishell(envp);
	return (0);
}
