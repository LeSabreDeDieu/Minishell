/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:31:50 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/31 16:34:58 by gcaptari         ###   ########.fr       */
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
	create_env(envp);
	print_env();
    test_env_encode = env_to_tab();
    printf("kjsdlfkdjflsk %s\n", test_env_encode[0]);
	free_env();
    free_str_tab(test_env_encode);
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
