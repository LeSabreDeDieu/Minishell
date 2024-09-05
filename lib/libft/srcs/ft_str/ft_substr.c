/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:30:43 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/02 16:32:40 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t		size;
	char		*new_str;

	if (!str)
		return (NULL);
	size = ft_strlen(str);
	if (start >= size || len == 0)
		return (ft_calloc(1, sizeof (char)));
	if ((size - start) < len)
		len = size - start;
	new_str = (char *) ft_calloc(len + 1, sizeof (char));
	if (new_str == NULL)
		return (NULL);
	return (ft_memmove(new_str, ((char *)str) + start, len));
}
