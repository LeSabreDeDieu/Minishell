/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:45:26 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/11 23:29:55 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	if (!str || c == 0)
		return (NULL);
	while (*str || c == 0)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
