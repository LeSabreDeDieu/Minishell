/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:47:27 by gcaptari          #+#    #+#             */
/*   Updated: 2024/06/02 16:48:53 by gcaptari         ###   ########.fr       */
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
