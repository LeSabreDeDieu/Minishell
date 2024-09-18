/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_factory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:09 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/18 12:15:25 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdbool.h>
#include <stdio.h>

t_env_factory	*get_env_factory(void)
{
	static t_env_factory	factory;

	if (!factory.instanced)
	{
		factory.instanced = 1;
		factory.config.sepparator = ft_strdup("=");
	}
	return (&factory);
}

t_parsing_env_config	*get_env_config(void)
{
	return (&get_env_factory()->config);
}
