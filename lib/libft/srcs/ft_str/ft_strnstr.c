/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:33:03 by sgabsi            #+#    #+#             */
/*   Updated: 2023/11/16 15:11:54 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	to_find_len;
	char	*next;

	if ((!str || !to_find) && len == 0)
		return (NULL);
	next = (char *)str;
	to_find_len = ft_strlen(to_find);
	if (to_find_len == 0)
		return ((char *)str);
	while (*next && to_find_len <= len--)
	{
		if (*next == *to_find && ft_memcmp(next, to_find, to_find_len) == 0)
		{
			return (next);
		}
		next++;
	}
	return (NULL);
}
