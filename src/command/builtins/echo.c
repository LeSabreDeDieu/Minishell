/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:45:31 by gcaptari          #+#    #+#             */
/*   Updated: 2024/09/19 16:53:12 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"

static bool	is_flags(char *flags)
{
	char	*move;

	if (!flags || !*flags)
		return (false);
	move = flags;
	while (*move)
	{
		if (*move != 'n')
			return (false);
		++move;
	}
	return (true);
}

int	echo_command(int argc, char *argv[])
{
	char	**tmp;
	bool	no_EOF;
	bool	is_write;

	if (!argv)
		return (125);
	no_EOF = false;
	is_write = false;
	if (argc > 1)
	{
		tmp = argv + 1;
		if (!tmp || !*tmp)
			return (125);
		while (tmp && *tmp)
		{
			if (!is_write && **tmp == '-' && is_flags(*tmp + 1))
			{
				no_EOF = true;
				++tmp;
				continue ;
			}
			(ft_putstr_fd(*tmp, 1), is_write = true);
			++tmp;
			*tmp != NULL && ft_putstr_fd(" ", 1);
		}
		!no_EOF && ft_putstr_fd("\n", 1);
	}
	return (EXIT_SUCCESS);
}
