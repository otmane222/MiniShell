/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 03:47:01 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/23 11:08:44 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	case_directory(char *str)
{
	DIR		*k;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	k = opendir(str);
	if (k)
	{
		ft_printf("Minishell: %s: is directory\n", \
			str);
		exit (126);
	}
}

char	*last_arg(char	**cmds)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (cmds[i])
	{
		str = cmds[i];
		i++;
	}
	return (str);
}

void	close_files(t_fds *list)
{
	while (list)
	{
		if (list->fd != 1 && list->fd != 0)
			close(list->fd);
		list = list->next;
	}
}

void	execute_execve(char *cmd, char **cmds, t_env *env, t_fds *list)
{
	char	**our_env;

	our_env = change_env(env);
	execve(cmd, cmds, our_env);
	free_2dd(our_env);
	close_files(list);
	ft_printf("Minishell: %s: command not found\n", cmd);
	if (errno == ENOENT)
		exit (127);
	exit (1);
}

char	*check_path(char **paths, char *path)
{
	int		i;
	char	*save;
	char	*tmp;

	i = 0;
	if (!paths)
		ft_printf("minishell: %s: No such file or directory\n", path);
	if (access(path, X_OK) == 0)
		return (path);
	save = path;
	path = ft_strjoin("/", path);
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], path);
		free (tmp);
		tmp = NULL;
		if (access(paths[i], X_OK) == 0)
			return (free(path), paths[i]);
		i++;
	}
	return (save);
}
