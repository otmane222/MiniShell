/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 05:29:21 by nakebli           #+#    #+#             */
/*   Updated: 2022/10/29 12:22:53 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp( const void *p1, const void *p2, size_t size )
{
	const unsigned char	*s1;
	const unsigned char	*s2;
	size_t				i;

	s1 = p1;
	s2 = p2;
	i = 0;
	if (size == 0)
		return (0);
	while (i < size -1 && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
