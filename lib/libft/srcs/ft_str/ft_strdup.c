/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:57:46 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/10 17:24:49 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;

	if (!s1 || !*s1)
		return (NULL);
	len = ft_strlen(s1);
	s2 = (char *)ft_calloc(len + 1, sizeof (char));
	if (!s2)
		return (NULL);
	return ((char *)ft_memmove(s2, s1, len));
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	char	*s2;

	if (!s1 || !*s1)
		return (NULL);
	len = ft_strlen(s1);
	if (len > n)
		len = n;
	s2 = (char *)ft_calloc(len + 1, sizeof (char));
	if (!s2)
		return (NULL);
	return ((char *)ft_memmove(s2, s1, len));
}
