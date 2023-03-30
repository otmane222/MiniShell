/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 07:50:00 by nakebli           #+#    #+#             */
/*   Updated: 2022/10/31 15:51:56 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isoverflow(long long int prev, long long curr)
{
	if (curr / 10 == prev)
		return (0);
	return (1);
}

static int	skip_spaces_get_signe(const char *str, int *signe)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '-')
	{
		*signe = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			a;
	int			*signe;
	long long	value;
	long long	prev;

	a = 1;
	signe = &a;
	value = 0;
	i = skip_spaces_get_signe(str, signe);
	while (str[i] <= '9' && str[i] >= '0')
	{
		prev = value;
		value = value * 10 + (str[i] - 48);
		if (ft_isoverflow(prev, value) == 1)
		{
			if (*signe == 1)
				return (-1);
			return (0);
		}
		i++;
	}
	return (*signe * value);
}
