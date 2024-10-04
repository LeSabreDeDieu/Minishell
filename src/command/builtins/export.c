/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:37:09 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/27 11:18:07 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	export_command(int argc, char **argv)
{
	t_parsing_env	parsing_env;
	int		i;

	(void)argc;
	i = 1;
	
	while (i < argc && argv[i])
	{
		parsing_env = parser_env(argv[i]);
		if (!parsing_env.name || !parsing_env.value)
			continue ;
		set_env(parsing_env.name, parsing_env.value);
		free(parsing_env.name);
		free(parsing_env.value);
		++i;
	}
	return (0);
}
