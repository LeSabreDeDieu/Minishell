/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:41:58 by sgabsi            #+#    #+#             */
/*   Updated: 2023/11/09 16:04:29 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed_str;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	if (!s1[start])
		return (ft_strdup(""));
	end = start + ft_strlen(s1 + start) - 1;
	while (end > 0 && is_in_set(s1[end], set))
		end--;
	trimmed_str = (char *)malloc(end - start + 2);
	if (!trimmed_str)
		return (NULL);
	i = 0;
	while (start <= end)
		trimmed_str[i++] = s1[start++];
	trimmed_str[i] = '\0';
	return (trimmed_str);
}
