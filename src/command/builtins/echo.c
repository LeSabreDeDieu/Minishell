/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:45:31 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/22 15:10:23 by sgabsi           ###   ########.fr       */
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

static void	print_args(char **tmp, int argc,  bool *no_eof, bool is_write)
{
	int i;

	i = 0;
	while (i < argc)
	{
		if (!is_write && **tmp == '-' && is_flags(*tmp + 1))
		{
			*no_eof = true;
			++tmp;
			continue ;
		}
		if(*tmp)
			(ft_putstr_fd(*tmp, STDOUT_FILENO), is_write = true, ++tmp);
		if (*tmp != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		++i;
	}
}

int	echo_command(int argc, char *argv[])
{
	char	**tmp;
	bool	no_eof;
	bool	is_write;

	if (!argv)
		return (125);
	no_eof = false;
	is_write = false;
	if (argc > 1)
	{
		tmp = argv + 1;
		if (!tmp || !*tmp)
			return (125);
		print_args(tmp, argc, &no_eof, is_write);
		if (!no_eof)
			ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}
