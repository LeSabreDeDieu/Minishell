/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:14:01 by sgabsi            #+#    #+#             */
/*   Updated: 2024/01/22 14:18:59 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptr_len(unsigned long long num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		num /= 16;
		len++;
	}
	return (len);
}

void	ft_put_ptr(uintptr_t num)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16);
		ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

int	ft_print_ptr(void *ptr)
{
	int					print_length;
	unsigned long long	mem;

	if (ptr == NULL)
		return (ft_printstr("(nil)"));
	mem = (unsigned long long)ptr;
	print_length = 0;
	print_length += write(1, "0x", 2);
	if (mem == 0)
		print_length += write(1, "0", 1);
	else
	{
		ft_put_ptr(mem);
		print_length += ft_ptr_len(mem);
	}
	return (print_length);
}
