/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:03:21 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/09 21:55:20 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_cd(char *path, t_env **env)
{
	char		*str;
	char		*str1;
	static int	i = 0;

	str = NULL;
	add_to_env("OLDPWD", str, env);
	if (chdir(path) != 0)
	{
		perror("cd");
		i = 1;
		return (1);
	}
	add_to_env("PWD", getcwd(NULL, 0), env);
	str = getcwd(NULL, 0);
	if (!str)
	{
		if (i == 2 || i == 0)
		{
			str1 = ft_strjoin(ft_getenv("PWD", *env), "/..");
			add_to_env("PWD", str1, env);
		}
		if (i == 0)
			ft_printf("minishell: cd: %s: No such file or directory\n", path);
		else
		{
			ft_printf("cd: error retrieving current directory: getcwd: cannot");
			ft_printf("access parent directories: No such file or directory\n");
		}
		i = 2;
		return (0);
	}
	free(str);
	return (0);
}
