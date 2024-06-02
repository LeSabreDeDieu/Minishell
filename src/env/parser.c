/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gcaptari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:36:35 by gcaptari          #+#    #+#             */
/*   Updated: 2024/06/02 16:42:21 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gcaptari <gabrielcaptari@student.42.fr>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/31 14:05:00 by gcaptari		  #+#	#+#			 */
/*   Updated: 2024/05/31 15:13:11 by gcaptari		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

static char	*parser_get_key(char *envp)
{
	char		*value;
	size_t		size_key;

	if (!envp)
		return (NULL);
	value = ft_strstr(envp, get_env_config()->sepparator);
	if (!value)
		return (NULL);
	size_key = value - envp;
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

static char	*ft_strjoin_env(char *name, char *separator, char *value)
{
	char	*tmp;
	char	*final;

	if (!name || !separator || !value)
		return (NULL);
	tmp = ft_strjoin(name, separator);
	if (!tmp)
		return (NULL);
	final = ft_strjoin(tmp, value);
	return (free(tmp), final);
}

char	**env_to_tab(void)
{
	t_env	*current;
	char	*tmp;
	char	**tabs;
	char	**move;

	tabs = ft_calloc(len_env() + 1, sizeof(char *));
	if (!tabs)
		return (NULL);
	move = tabs;
	current = get_env_factory()->env;
	while (current)
	{
		tmp = ft_strjoin_env(current->name,
				get_env_factory()->config.sepparator, current->value);
		if (!tmp)
			return (free_str_tab(tabs), NULL);
		*move++ = tmp;
		current = current->next;
	}
	return (tabs);
}
