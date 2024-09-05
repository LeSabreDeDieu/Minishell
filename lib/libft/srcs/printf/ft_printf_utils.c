/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:50:41 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/18 14:26:37 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	else
	{
		while (str[i])
		{
			ft_putchar_fd(str[i], 1);
			i++;
		}
	}
	return (i);
}

int	ft_printnbr(int n)
{
	int		len;
	char	*num;

	num = ft_itoa(n);
	len = ft_printstr(num);
	free(num);
	return (len);
}

int	ft_printpourcent(void)
{
	write(1, "%", 1);
	return (1);
}
