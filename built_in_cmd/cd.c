/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:03:21 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/11 13:06:16 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	cd_call(int i, char *path, t_env **env)
{
	if (i == 0)
	{
		ft_printf("minishell: cd1: %s: No such file or directory\n", path);
		return (i = 1, g_exit_status = 1, 1);
	}
	else
	{
		ft_printf("cd: error retrieving current directory: getcwd: cannot");
		ft_printf("access parent directories: No such file or directory\n");
	}
	add_to_env("PWD", ft_strjoin(ft_getenv("PWD", *env), "/.."), env);
	return (g_exit_status = 1, 1);
}

int	telde(char *line, t_env *our_env)
{
	char	*str;

	str = ft_getenv("HOME", our_env);
	if (str)
	{
		edit_env("OLDPWD", getcwd(NULL, 0), &our_env);
		if (chdir(str) != 0)
		{
			perror("cd");
			return (1);
		}
		edit_env("PWD", getcwd(NULL, 0), &our_env);
	}
	else
	{
		if (chdir(line) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	if (str)
		free (str);
	return (0);
}

static int	ret_old_pwd(t_env **env, char *path)
{
	char	*str;
	char	*tmp;

	if (!ft_strncmp(path, "~", 2))
		return (telde(path, *env));
	str = ft_getenv("OLDPWD", *env);
	if (!str)
		return (ft_printf("minishell: cd: OLDPWD not set\n"), 1);
	tmp = ft_getenv("PWD", *env);
	edit_env("OLDPWD", tmp, env);
	if (chdir(str) != 0)
	{
		if (str)
			free (str);
		perror("cd");
		return (1);
	}
	edit_env("PWD", getcwd(NULL, 0), env);
	ft_pwd(1, env, 0);
	if (str)
		free (str);
	return (0);
}

int	ft_cd(char *path, t_env **env)
{
	char		*str;
	static int	i = 0;

	if (!path)
		return (1);
	if (!ft_strncmp(path, "-", 2) || !ft_strncmp(path, "~", 2))
		return (ret_old_pwd(env, path));
	str = getcwd(NULL, 0);
	if (!str && i == 0)
	{
		ft_printf("minishell: cd1: %s: No such file or directory\n", path);
		return (i = 1, g_exit_status = 1, 1);
	}
	free(str);
	edit_env("OLDPWD", getcwd(NULL, 0), env); // add_to_env or edit_env
	if (chdir(path) != 0)
	{
		perror("cd");
		return (g_exit_status = 1, 1);
	}
	edit_env("PWD", getcwd(NULL, 0), env);
	str = getcwd(NULL, 0);
	if (!str)
		return (cd_call(i, path, env));
	if (str)
		free(str);
	return (g_exit_status = 0, 0);
}
