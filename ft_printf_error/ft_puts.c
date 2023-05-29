/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 00:30:39 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/29 14:29:58 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *len)
{
	if (write(2, &c, 1))
	{
		*len += 1;
		return ;
	}
	*len = -1;
}

void	ft_putstr(char *s, int *len)
{
	if (!s)
	{
		write (1, "(null)", 6);
		*len += 6;
		return ;
	}	
	while (*s)
	{
		ft_putchar(*s, len);
		s++;
	}
}

void	ft_putnbr_long(unsigned int nb, int *len)
{
	if (nb < 0)
	{
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10, len);
		ft_putnbr(nb % 10, len);
	}
	else
		ft_putchar(nb + '0', len);
}
