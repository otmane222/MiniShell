/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:23:49 by nakebli           #+#    #+#             */
/*   Updated: 2022/10/29 12:17:23 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove( void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*d;
	char			*s;

	d = dest;
	s = (char *)src;
	i = -1;
	if (s == d || !n)
		return (d);
	else if (s > d)
	{
		while (++i < n)
		{
			d[i] = s[i];
		}
	}
	else
	{
		while (++i <= (n - 1))
		{
			d[n - 1 - i] = s[n - 1 - i];
		}
	}
	return (d);
}
