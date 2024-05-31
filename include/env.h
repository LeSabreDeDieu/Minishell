/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaptari <gabrielcaptari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:08 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/31 15:12:09 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "libft.h"
# include <stdbool.h>

typedef struct s_env
{
	struct s_env			*next;
	char					*name;
	char					*value;
}							t_env;

typedef struct s_parsing_env
{
	char					*name;
	char					*value;
}							t_parsing_env;

typedef struct s_parsing_env_config
{
	char					*sepparator;
}							t_parsing_env_config;

typedef struct s_env_factory
{
	t_env					*env;
	t_parsing_env_config	config;
	char					instanced;
}							t_env_factory;

t_env_factory				*get_env_factory(void);
t_parsing_env_config		*get_env_config(void);

t_env						*get_env(char *name);
void						set_env(char *name, char *value);

t_env						*new_env(char *name, char *value);
void						add_env(t_env *env);
void						create_env(char *envp[]);
void						print_env(void);
void						free_env(void);

t_parsing_env				parser_env(char *envp);

#endif