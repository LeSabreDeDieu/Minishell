/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:42:02 by gcaptari          #+#    #+#             */
/*   Updated: 2024/06/20 13:34:47 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "env.h"

int unset_command(int argc, char *argv[])
{
	char **move;

	if (argc > 1)
	{
		move = (argv + 1);
		if (!move || !*move)
			return (125);
		while (*move)
			unset_env(*move++);
		return (1);
	}
	return (0);
}
