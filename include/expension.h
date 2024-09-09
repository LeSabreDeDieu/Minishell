/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:16:42 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/09 13:34:36 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPENSION_H
# define EXPENSION_H

# include "ast.h"

typedef struct s_ast_value	t_ast_value;

void	expend_variable(t_ast_value *value);

#endif