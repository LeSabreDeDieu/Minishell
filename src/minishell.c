/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:28:15 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/19 12:41:28 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "stdbool.h"

#include "test.h"

int	minishell(t_minishell *data, char *prompt)
{
	to_tokenise(data, prompt);
	free(prompt);
	print_token(data->tokens);
	if (!check_valid_token(data->tokens))
	{
		ft_putendl_fd("TOKEN ERROR !", 2);
		return (free(data->tokens), false);
	}
	create_ast(data, data->tokens);
	print_ast(data->ast);
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
		ft_putstr_fd("What did you do that ?", 2);
		ft_putstr_fd("why did you gave to me some arguments ?\n", 2);
	}
	ft_bzero(&data, sizeof(t_minishell));
	create_env(envp);
	ft_putendl_fd("Welcome to minishell", 1);
	while (true)
	{
		line = rl_gets();
		if (!line)
		{
			free_env();
			free_token(data.tokens);
			free(data.tokens);
			exit(0);
		}
		minishell(&data, line);
	}
	return (0);
}
