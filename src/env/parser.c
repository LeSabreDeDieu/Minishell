/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:05:00 by gcaptari          #+#    #+#             */
/*   Updated: 2024/05/31 15:13:11 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

static char	*parser_get_key(char *envp)
{
	const char	*value;
	size_t		size_key;

	if (!envp)
		return (NULL);
	value = ft_strstr(envp, get_env_config()->sepparator);
	if (!value)
		return (NULL);
	size_key = value - envp - 1;
	return (ft_substr(envp, 0, size_key));
}

static char	*parse_get_value(char *envp)
{
	const char	*value;

	if (!envp)
		return (NULL);
	value = ft_strstr(envp, get_env_config()->sepparator) + 1;
	if (!value)
		return (NULL);
	return (ft_strdup(value));
}
t_parsing_env	parser_env(char *envp)
{
	char	*key;
	char	*value;
	key = parser_get_key(envp);
	if (!key)
		return ((t_parsing_env){.name = NULL, .value = NULL});
	value = parse_get_value(envp);
	if (!value)
		return (free(key), (t_parsing_env){.name = NULL, .value = NULL});
	return ((t_parsing_env){.name = key, .value = value});
}