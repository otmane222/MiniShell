/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:53:48 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/06 18:50:57 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	open_rest(t_tree *root, int type)
{
	int	fd;

	fd = -1;
	if (type == RED_IN)
	{
		fd = open(root->token->cmd[0], O_RDONLY, 0644);
		if (fd == -1)
			return (printf ("minishell: %s: No such file or directory\n", \
				root->token->cmd[0]), -1);
	}
	else if (type == D_RED_IN)
	{
		fd = open(root->token->cmd[0], O_RDONLY | O_EXCL, 0644);
		if (fd == -1)
			return (printf ("minishell: %s: No such file or directory\n", \
				root->token->cmd[0]), -1);
	}
	return (fd);
}

int	file_opened(t_tree *root, int type)
{
	int	check;

	check = 0;
	if (type == RED_OUT)
	{
		check = open(root->token->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (check == -1)
			return (printf ("minishell: %s: No such file or directory\n", \
				root->token->cmd[0]), -1);
	}
	else if (type == D_RED_OUT)
	{
		check = open(root->token->cmd[0], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (check == -1)
			return (printf ("minishell: %s: No such file or directory\n", \
				root->token->cmd[0]), -1);
	}
	else
	{
		check = open_rest(root, type);
		if (check == -1)
			return (-1);
	}
	return (check);
}

int	open_red(t_tree *root, t_env *env, int type)
{
	char	*tmp;
	char	*str;
	int		check;

	check = 0;
	tmp = root->token->cmd[0];
	str = ft_strdup(root->token->cmd[0]);
	root->token->cmd[0] = handle_wildcard_char(root->token->cmd[0]);
	if (short_cut4(root, tmp, str, env))
		return (-1);
	free(str);
	root->token->cmd[0] = deleted_q(root->token->cmd[0]);
	check = file_opened(root, type);
	if (check == -1)
		return (-1);
	return (check);
}

static int	fd_to_out_append(t_tree *root, t_env *env, \
			t_data *data, t_fds **list)
{
	(void)env;
	if (openfiles(root, data, env, list))
		return (1);
	return (0);
}

int	append(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	data.j = fd_to_out_append(root, *env, &data, list);
	if (data.j == 1)
		return (g_exit_status = 1, 1);
	data.status = execute_cmd(root->left, data, env, list);
	if (data.status == 1)
		return (1);
	return (0);
}
