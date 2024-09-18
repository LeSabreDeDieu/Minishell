/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:50:02 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/17 15:11:45 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*allocate_new_str(size_t old_len, size_t old_sub_len,
		size_t new_sub_len)
{
	size_t	new_len;
	char	*new_str;

	new_len = old_len + (new_sub_len - old_sub_len) + 1;
	new_str = ft_calloc(new_len, sizeof(char *));
	if (!new_str)
		return (NULL);
	return (new_str);
}

static void	copy_and_replace(char *dest, const char *src, const char *old_sub,
		const char *new_sub)
{
	const char	*temp;
	size_t		segment_len;
	size_t		old_sub_len;
	size_t		new_sub_len;

	old_sub_len = ft_strlen(old_sub);
	new_sub_len = ft_strlen(new_sub);
	temp = src;
	temp = ft_strstr(temp, old_sub);
	if (temp != NULL)
	{
		segment_len = temp - src;
		ft_memcpy(dest, src, segment_len);
		dest += segment_len;
		ft_memcpy(dest, new_sub, new_sub_len);
		dest += new_sub_len;
		temp += old_sub_len;
		src = temp;
	}
	ft_strlcpy(dest, src, ft_strlen(src) + 1);
}

char	*ft_str_replace(char *str, char *old_sub, char *new_sub)
{
	char	*new_str;
	size_t	old_len;
	size_t	old_sub_len;
	size_t	new_sub_len;

	if (!str || !old_sub || !new_sub)
		return (NULL);
	old_len = ft_strlen(str);
	old_sub_len = ft_strlen(old_sub);
	new_sub_len = ft_strlen(new_sub);
	new_str = allocate_new_str(old_len, old_sub_len, new_sub_len);
	if (!new_str)
		return (NULL);
	copy_and_replace(new_str, str, old_sub, new_sub);
	free(str);
	return (new_str);
}
