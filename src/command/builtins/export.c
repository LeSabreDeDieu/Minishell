/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/10/04 15:30:58 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/04 15:30:58 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "ms_error.h"

static bool	ft_str_isprint(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (!ft_isprint(*tmp++))
			return (false);
	}
	return (true);
}

bool	is_valid_name(char *name)
{
	if (ft_isdigit(name[0]))
	{
		error_message_command_with_arg("export", name,
			"not a valid identifier");
		return (false);
	}
	return (true);
}

int	export_command(int argc, char **argv)
{
	t_parsing_env	parsing_env;
	int				i;

	(void)argc;
	i = 1;
	while (i < argc && argv[i])
	{
		if (!is_valid_name(argv[i]))
		{
			i++;
			continue ;
		}
		parsing_env = parser_env(argv[i]);
		if (!parsing_env.name || !parsing_env.value)
		{
			++i;
			continue ;
		}
		if (!ft_isdigit(parsing_env.name[0])
			&& ft_str_isprint(parsing_env.name))
			set_env(parsing_env.name, parsing_env.value);
		(free(parsing_env.name), free(parsing_env.value));
		++i;
	}
	return (0);
}
