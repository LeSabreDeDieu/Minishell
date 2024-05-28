/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:52:55 by sgabsi            #+#    #+#             */
/*   Updated: 2023/11/16 14:59:25 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int		i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	if (n == 0)
		return (0);
	i = 0;
	str1 = (const unsigned char *) s1;
	str2 = (const unsigned char *) s2;
	while ((str1[i] && str2[i]) && str1[i] == str2[i] && i < n - 1)
		i++;
	return (str1[i] - str2[i]);
}
