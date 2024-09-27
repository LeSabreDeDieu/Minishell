/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:41:08 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/27 10:23:19 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

bool	is_dollar_allone(t_ast_value *value, t_pos *pos)
{
	return (value->argv[(*pos).i][(*pos).j] == '$'
			&& (ft_isspace(value->argv[(*pos).i][(*pos).j + 1])
				|| !value->argv[(*pos).i][(*pos).j + 1]));
}
