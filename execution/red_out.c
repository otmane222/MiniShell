/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:16:01 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/01 22:05:47 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	fd_to_out(t_tree *root)
{
	int	fd;

	root = root->right;
	while (root->left)
	root = root->left;
	if (root && root->token->type == FILE)
	{
		fd = open(root->token->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0655);
		if (fd == -1)
		{
			printf ("Minishell: %s: No such file or directory\n", \
				root->token->cmd[0]);
			return (1);
		}
		return (fd);
	}
	return (1);
}

int	red_out_hanlde(t_tree *root, t_data data, t_env **env, t_fds *list)
{
	int	k;

	data.j = fd_to_out(root);
	if (data.j == 1)
		return (1);
	add_b_list(&list, init_list(data.j));
	k = data.outfile_fd;
	if (!data.redout)
		data.outfile_fd = data.j;
	data.redout = RED_OUT;
	data.status = execute_cmd(root->left, data, env, list);
	if (data.status == 1)
		return (1);
	data.outfile_fd = k;
	data.status = execute_cmd(root->right, data, env, list);
	if (data.status == 1)
		return (1);
	close(data.j);
	return (0);
}
