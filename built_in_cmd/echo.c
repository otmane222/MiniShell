/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:34:33 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/20 13:20:13 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	call_help(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i] && i != 1)
		return (1);
	return (0);
}

static void	help_cal(char *arg, int *flag)
{
	if (call_help(arg))
		*flag = 1;
	else
		*flag = 2;
}

void	ft_echo(int outfile, char **arg)
{
	int		i;
	int		flag;

	flag = 0;
	i = 1;
	while (arg[i] && arg[i][0] == '-')
	{
		help_cal(arg[i], &flag);
		if (flag == 2)
			break ;
		i++;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], outfile);
		if (arg[i + 1])
			ft_putchar_fd(' ', outfile);
		if (!arg[i + 1] && !flag)
			write (outfile, "\n", 1);
		i++;
	}
	if (flag == 2 || !arg[1])
		write (outfile, "\n", 1);
	g_exit_status = 0;
}
