/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:01:37 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/19 16:54:18 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hexx(unsigned int number, int *len)
{
	if (number <= 15 && *len != -1)
	{
		ft_putchar("0123456789ABCDEF"[number], len);
	}
	else if (number > 15)
	{
		ft_hexx(number / 16, len);
		ft_hexx(number % 16, len);
	}
}

void	ft_hex(unsigned long int number, int *len)
{
	if (number <= 15 && *len != -1)
	{
		ft_putchar("0123456789abcdef"[number], len);
	}
	else if (number > 15)
	{
		ft_hex(number / 16, len);
		ft_hex(number % 16, len);
	}
}

void	ft_hexp(void *ptr, int *len)
{
	ft_putchar('0', len);
	ft_putchar('x', len);
	ft_hex((unsigned long int)ptr, len);
}

void	ft_putnbr(int nb, int *len)
{
	char	c;

	if (nb == -2147483648)
	{
		ft_putstr("-2147483648", len);
		return ;
	}
	else if (nb >= 0 && nb <= 9 && *len > -1)
	{
		c = nb + 48;
		write (1, &c, 1);
		*len += 1;
	}
	else if (nb < 0)
	{
		write (1, "-", 1);
		*len += 1;
		ft_putnbr (-nb, len);
	}
	else if (nb > 0)
	{
		ft_putnbr (nb / 10, len);
		ft_putnbr (nb % 10, len);
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	len = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (*format)
	{
		while (*format != '%' && *format)
		{
			ft_putchar (*format, &len);
			format++;
		}
		if (*format && ft_get_format(*(format + 1)) > 0)
		{
			ft_print_fortmat(ft_get_format(*(format + 1)), args, &len);
			format++;
		}
		if (!(*format))
			break ;
		format++;
	}
	va_end(args);
	return (len);
}
