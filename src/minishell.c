/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:31:50 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/02 17:10:08 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

// void	ft_handle_signal(int signum, siginfo_t *info, void *context)
// {
// 	char	*str;

// 	(void)info;
// 	(void)context;
// 	str = get_env("USER")->value;
// 	if (signum == SIGINT)
// 	{
// 		rl_replace_line("\0", 1);
// 		rl_redisplay();
// 	}
// 	return ;
// }

int	main(int argc, char *argv[], char *envp[])
{
	// struct sigaction	sa;
	// char	*prompt;
	char **test_env_encode;

	(void)argc;
	(void)argv;
	if(!test_env_config())
		return (0);
	create_env(envp);
	print_env();
	test_env_encode = env_to_tab();
	if (test_env_encode)
	{
		printf("kjsdlfkdjflsk %s\n", test_env_encode[0]);
		free_str_tab(test_env_encode);
	}
	set_env("PP", "test");
	print_env();
	free_env();
	// sa.sa_sigaction = &ft_handle_signal;
	// sa.sa_flags = SA_SIGINFO;
	// sigaction(SIGINT, &sa, NULL);
	// sigaction(SIGQUIT, &sa, NULL);
	// while (1)
	// {
	// 	printf("%s", get_env("USER").value);
	// 	prompt = readline("> ");
	// 	// if (!prompt)
	// 	// {
	// 	// 	free_env();
	// 	// 	exit(0);
	// 	// }
	// 	// if (!rl_on_new_line())
	// 	// 	printf("%s", prompt);
	// }
	return (0);
}
