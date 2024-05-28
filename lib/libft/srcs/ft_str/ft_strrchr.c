/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:45:26 by sgabsi            #+#    #+#             */
/*   Updated: 2023/11/07 20:35:58 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*last_char;

	last_char = NULL;
	while (*str)
	{
		if (*str == (char)c)
			last_char = (char *)str;
		str++;
	}
	if (c == 0)
		return ((char *)str);
	return (last_char);
}
