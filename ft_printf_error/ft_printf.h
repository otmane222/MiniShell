/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:11:24 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/19 16:51:32 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

void	ft_putchar(char c, int *len);
int		ft_printf(const char *format, ...);
void	ft_putnbr(int nb, int *len);
void	ft_putnbr_long(unsigned int nb, int *len);
void	ft_hex(unsigned long int number, int *len);
void	ft_hexp(void *ptr, int *len);
void	ft_hexx(unsigned int nnumber, int *len);
void	ft_putstr(char *s, int *len);
void	ft_print_fortmat(int format, va_list ptr, int *len);
int		ft_get_format(char text);

#endif