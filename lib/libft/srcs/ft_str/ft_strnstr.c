/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:33:03 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/09 13:54:36 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_max(size_t n, size_t n2)
{
	if (n > n2)
		return (n);
	return (n2);
}

static void	ft_skip_table(size_t list_ascii[256], unsigned char *needle,
		const size_t n_len)
{
	size_t	i;

	i = 0;
	while (i < 256)
		list_ascii[i++] = n_len;
	i = 0;
	while (i < n_len - 1)
	{
		list_ascii[(size_t)needle[i]] = ft_max((n_len - i - 1), 1);
		i++;
	}
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	const size_t	n_len = ft_strlen(needle);
	size_t			h_len;
	size_t			list_ascii[256];
	size_t			i;

	if (n_len == 0)
		return ((char *)haystack);
	if (needle == haystack)
		return ((char *)haystack);
	h_len = ft_strlen(haystack);
	if (n_len > h_len)
		return (NULL);
	ft_skip_table(list_ascii, (unsigned char *)needle, n_len);
	i = 0;
	while (i <= h_len - n_len)
	{
		if ((unsigned char)haystack[i + n_len - 1]
			== (unsigned char)needle[n_len - 1])
			if (ft_memcmp(haystack + i, needle, n_len - 1) == 0)
				return ((char *)(haystack + i));
		i += list_ascii[(size_t)((unsigned char)haystack[i + n_len - 1])];
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	const size_t	n_len = ft_strlen(needle);
	size_t			h_len;
	size_t			list_ascii[256];
	size_t			i;

	if (n_len == 0)
		return ((char *)haystack);
	if (n == 0)
		return (NULL);
	h_len = ft_strlen(haystack);
	if (n < n_len || n_len > h_len)
		return (NULL);
	ft_skip_table(list_ascii, (unsigned char *)needle, n_len);
	i = 0;
	while (i <= h_len && i <= n && i <= (n - n_len))
	{
		if ((unsigned char)haystack[i + n_len - 1]
			== (unsigned char)needle[n_len - 1])
			if (ft_memcmp(haystack + i, needle, n_len - 1) == 0)
				return ((char *)(haystack + i));
		i += list_ascii[(size_t)((unsigned char)haystack[i + n_len - 1])];
	}
	return (NULL);
}
