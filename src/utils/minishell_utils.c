/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:14:37 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/16 13:19:22 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_from_void(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	set_env("PWD", pwd);
	free(pwd);
	set_env("SHLVL", "0");
	set_env("_", "/usr/bin/env");
}
