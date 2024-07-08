/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:45:31 by gcaptari          #+#    #+#             */
/*   Updated: 2024/06/20 13:22:46 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"

static char	*ft_strjoin_with(char *name, char *separator, char *value)
{
	char	*tmp;
	char	*final;

	if (!name || !separator || !value)
		return (NULL);
	tmp = ft_strjoin(name, separator);
	if (!tmp)
		return (NULL);
	final = ft_strjoin(tmp, value);
	return (free(tmp), final);
}

int	echo_command(int argc, char *argv[])
{
	char **tmp;
	char *echo_tmp;
	char *echo;

	if(!argv)
		return (125);
	echo = NULL;
	if (argc > 1)
	{
		tmp = argv + 1;
		if (!tmp || !*tmp)
			return (125);
		while (*tmp)
		{
			if (!echo)
			{
				echo = ft_strdup(*tmp);
				if (!echo)
					return (125);
			}
			else
			{
				echo_tmp = echo;
				echo = ft_strjoin_with(echo_tmp, " ", *tmp);
				free(echo_tmp);
				if(!echo)
					return (125);
			}
			++tmp;
		}
		(ft_putstr_fd(echo, 1), free(echo));
	}
	return (0);
}