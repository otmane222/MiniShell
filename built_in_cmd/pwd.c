/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:33:24 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/26 02:46:20 by oaboulgh         ###   ########.fr       */
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
	g_exit_status = 1;
}

void	ft_init(t_env **env)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		print_error(1);
		g_exit_status = 1;
		return ;
	}
	add_to_env(ft_strdup("PWD"), str, env);
}

char	*get_save(char *save, char *path)
{
	char		*tmp;

	if (ft_strncmp(save, "/..", 4) == 0)
	{
		tmp = path;
		path = ft_strjoin (tmp, "/..");
		return (free(tmp), path);
	}
	if (path)
		free(path);
	return (path = save, path);
}

int	ft_pwd(int outfile, __attribute__((unused)) t_env **env, char *save)
{
	static char	*path;
	char		*str;

	if (save)
		return (path = get_save(save, path), 0);
	str = getcwd(NULL, 0);
	if (!str)
	{
		if (!path)
			return (print_error(2), g_exit_status = 1, 1);
		str = path;
		ft_putstr_fd(str, outfile);
		write(outfile, "\n", 1);
		return (0);
	}
	if (path)
		free(path);
	path = str;
	ft_putstr_fd(str, outfile);
	write(outfile, "\n", 1);
	return (g_exit_status = 0, 0);
}
