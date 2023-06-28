/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:27:27 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/28 17:19:58 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_format(char text)
{
	if (text == 'd' || text == 'i')
		return (1);
	else if (text == 'x')
		return (2);
	else if (text == 'X')
		return (3);
	else if (text == 'p')
		return (4);
	else if (text == 's')
		return (5);
	else if (text == 'c')
		return (6);
	else if (text == 'u')
		return (7);
	else if (text == '%')
		return (8);
	return (0);
}

void	ft_print_fortmat(int format, va_list ptr, int *len)
{
	if (format == 0)
		return ;
	else if (format == 5)
		ft_putstr(va_arg(ptr, char *), len);
	else if (format == 1)
		ft_putnbr(va_arg(ptr, int), len);
	else if (format == 2)
		ft_hex(va_arg(ptr, unsigned int), len);
	else if (format == 3)
		ft_hexx(va_arg(ptr, unsigned int), len);
	else if (format == 4)
		ft_hexp(va_arg(ptr, void *), len);
	else if (format == 6)
		ft_putchar(va_arg(ptr, int), len);
	else if (format == 7)
		ft_putnbr_long(va_arg(ptr, unsigned int), len);
	else if (format == 8)
		ft_putchar('%', len);
	else if (format == 0)
		return ;
}
