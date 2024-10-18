/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:42:02 by gcaptari          #+#    #+#             */
/*   Updated: 2024/10/18 12:53:00 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "env.h"

int	unset_command(t_minishell *shell_data, int argc, char *argv[])
{
	char	**move;

	if (argc > 1)
	{
		move = (argv + 1);
		if (!move || !*move)
			return (125);
		while (*move)
		{
			if (is_exact_name(*move, "PATH"))
			{
				free(shell_data->data.path);
				shell_data->data.path = NULL;
			}
			unset_env(*move++);
		}
		return (1);
	}
	return (0);
}
