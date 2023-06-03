/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:01:55 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/01 22:05:43 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	fd_to_in(t_tree *root)
{
	int	fd;

	root = root->right;
	while (root->left)
		root = root->left;
	if (root->token->type == FILE)
	{
		fd = open(root->token->cmd[0], O_RDONLY, 0655);
		if (fd == -1)
		{
			printf ("minishell: %s: No such file or directory\n", root->token->cmd[0]);
			return (1);
		}
		return (fd);
	}
	return (0);
}

int	handle_red_in(t_tree *root, t_data data, t_env **env, t_fds *list)
{
	int	k;

	data.j = fd_to_in(root);
	if (data.j == 1)
		return (1);
	add_b_list(&list, init_list(data.j));

	k = data.infile_fd;

	if (!data.redin)
		data.infile_fd = data.j;
	data.redin = RED_IN;
	data.status = execute_cmd(root->left, data, env, list);
	if (data.status == 1)
		return (1);
	data.infile_fd = k;
	data.status = execute_cmd(root->right, data, env, list);
	if (data.status == 1)
		return (1);
	close(data.j);
	return (0);
}
