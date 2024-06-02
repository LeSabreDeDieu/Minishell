/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:31:50 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/02 18:29:10 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	**test_env_encode;

	(void)argc;
	(void)argv;
	if (!test_env_config())
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
	return (0);
}
