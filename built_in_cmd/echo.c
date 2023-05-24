/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:34:33 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/23 22:06:11 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	help_cal(char *arg, int *flag, int *i)
{
	if (ft_strncmp(arg, "-n", 3) == 0 && \
	ft_strlen(arg) == 2)
	{
		(*i) = 2;
		*flag = 1;
	}
}

void	ft_echo(int outfile, char **arg)
{
	int		i;
	int		flag;

	flag = 0;
	i = 1;
	if (arg[i])
		help_cal(arg[i], &flag, &i);
	while (arg[i])
	{
		ft_putstr_fd(arg[i], outfile);
		if (arg[i + 1])
			ft_putchar_fd(' ', outfile);
		if (!arg[i + 1] && !flag)
			write (outfile, "\n", 2);
		i++;
	}
}
