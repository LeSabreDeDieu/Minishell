/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:31:50 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/13 10:59:31 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	char *line;

	if (!test_env_config())
		return (0);
	create_env(envp); 
	print_env();
	while (true)
	{
		line = rl_gets();
		if (!line)
		{
			free_env();
			return (0);
		}
		printf("%s\n", line);
	}
	return (0);
}
