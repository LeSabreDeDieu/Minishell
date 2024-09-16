/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:07:10 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/11 23:48:26 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

bool	wildcard_in_quote(char *str)
{
	if (ft_strchr(str, '"') == NULL && ft_strchr(str, '\'') == NULL)
		return (0);
	else if (ft_strchr(str, '"') != NULL)
		return ((ft_strchr(str, '"') < ft_strchr(str, '*') && ft_strchr(str,
					'*') < ft_strchr(ft_strchr(str, '"') + 1, '"')));
	else
		return ((ft_strchr(str, '\'') < ft_strchr(str, '*') && ft_strchr(str,
					'*') < ft_strchr(ft_strchr(str, '\'') + 1, '\'')));
}
