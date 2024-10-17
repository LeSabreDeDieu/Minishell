/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:47:27 by gcaptari          #+#    #+#             */
/*   Updated: 2024/07/10 16:14:41 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdbool.h>

bool	test_env_config(void)
{
	t_parsing_env_config	*config;

	config = get_env_config();
	if (!config->sepparator)
		return (false);
	return (true);
}
