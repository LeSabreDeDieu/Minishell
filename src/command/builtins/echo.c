/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:45:31 by gcaptari          #+#    #+#             */
/*   Updated: 2024/09/05 10:24:15 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"

static bool	is_flags(char *flags)
{
	char	*move;

	if(!flags || !*flags)
		return (false);
	move = flags;
	while(*move)
	{
		if(*move != 'n')
			return (false);
		++move;
	}
	return (true);
}

int	echo_command(int argc, char *argv[])
{
	char **tmp;
	bool	no_EOF;

	if(!argv)
		return (125);
	no_EOF = false;
	if (argc > 1)
	{
		tmp = argv + 1;
		if (!tmp || !*tmp)
			return (125);
		while (tmp && *tmp)
		{
			if(**tmp == '-' && is_flags(*tmp + 1))
			{
				no_EOF = true;
				++tmp;
				continue ;
			}
			ft_putstr_fd(*tmp, 1);
			if (*(tmp  + 1 )!= NULL)
				ft_putstr_fd(" ", 1);
			++tmp;
		}
		if(!no_EOF)
			ft_putstr_fd("\n", 1);
	}
	return (0);
}
