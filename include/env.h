/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:45:00 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/08 13:02:15 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h>

# include "libft.h"
# include "utils.h"

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
	size_t					length;
	t_parsing_env_config	config;
	bool					instanced;
}							t_env_factory;

t_env_factory				*get_env_factory( void );
t_parsing_env_config		*get_env_config( void );
bool						test_env_config( void );

t_env						*get_env( char *name );
void						set_env( char *name, char *value);
void						unset_env( char *name );

t_env						*new_env( char *name, char *value);
size_t						len_env( void );
void						print_env( void );
void						free_env( void );
void						add_env( t_env *env );
void						create_env( char *envp[] );

t_parsing_env				parser_env( char *env );
char						**env_to_tab( void );

#endif