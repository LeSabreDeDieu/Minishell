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
	char	**split;
	char	*value;
	int		i;

	(void)argc;
	i = 0;
	while (argv[i])
	{
		split = ft_split(argv[i], '=');
		value = ft_strtrim(split[1], "\"");
		set_env(split[0], value);
		free_str_tab(split);
		free(value);
		i++;
	}
	return (0);
}
