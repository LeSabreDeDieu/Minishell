/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:38:06 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/04 17:33:20 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

bool	is_exact_name(char *name, char *equal)
{
	size_t	len;
	size_t	len_eq;

	len = ft_strlen(name);
	len_eq = ft_strlen(equal);
	return (ft_strncmp(name, equal, len) == 0 && ft_strncmp(equal, name,
			len_eq) == 0);
}

bool	is_builtin(char *name)
{
	return (is_exact_name(name, "echo") || is_exact_name(name, "cd")
		|| is_exact_name(name, "exit") || is_exact_name(name, "env")
		|| is_exact_name(name, "unset") || is_exact_name(name, "export")
		|| is_exact_name(name, "pwd"));
}

char	*special_cmd_join(char *path, char *name)
{
	char	*cmd_path;
	char	*cmd_file;

	cmd_path = ft_strjoin(path, "/");
	if (!cmd_path)
		return (NULL);
	cmd_file = ft_strjoin(cmd_path, name);
	free(cmd_path);
	return (cmd_file);
}
