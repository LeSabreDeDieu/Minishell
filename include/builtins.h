/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:49:33 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/17 16:43:23 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		builtin_cd(t_minishell *data, char **argv);
int		builtin_echo(t_minishell *data, char **argv);
int		builtin_env(t_minishell *data, char **argv);
int		builtin_exit(t_minishell *data, char **argv);
int		builtin_export(t_minishell *data, char **argv);
int		builtin_pwd(t_minishell *data, char **argv);
int		builtin_unset(t_minishell *data, char **argv);

#endif
