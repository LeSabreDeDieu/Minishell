/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:24:32 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/10 16:37:13 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

bool	is_in_quote(char c, bool is_quoted)
{
	if (c == '"' && is_quoted == false)
		return (true);
	else if (c == '"' && is_quoted == true)
		return (false);
	else
		return (is_quoted);
}
