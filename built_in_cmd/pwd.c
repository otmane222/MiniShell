/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:33:24 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/20 15:58:56 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_error(int i)
{
	if (i == 1)
		ft_printf("shell-init: ");
	if (i == 2)
		ft_printf("pwd: ");
	if (i == 3)
		ft_printf("cd: ");
	ft_printf("error retrieving current directory: getcwd:");
	ft_printf(" cannot access parent directories: No such file or");
	ft_printf("directory\n");
}

int	ft_pwd(int outfile, __attribute__((unused)) t_env **env, int flag)
{
	static char	*path;
	char		*str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		if (!path)
		{
			if (flag == 1)
				return (print_error(1), g_exit_status = 1, 1);
			return (print_error(2), g_exit_status = 1, 1);
		}
		str = path;
	}
	if (flag == 1)
		return (free(str), 0);
	if (path)
		free(path);
	path = str;
	ft_putstr_fd(str, outfile);
	write(outfile, "\n", 1);
	return (g_exit_status = 0, 0);
}
