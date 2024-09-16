/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:04:53 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/16 16:30:08 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	add_shlvl(void)
{
	t_env	*env;
	char	*env_value;
	int		shlvl;

	shlvl = 0;
	env = get_env("SHLVL");
	if (env)
		env_value = env->value;
	shlvl = ft_atoi(env_value);
	env_value = ft_itoa(++shlvl);
	set_env("SHLVL", env_value);
	free(env_value);
}
