/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:53:48 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/01 22:05:50 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	fd_to_out_append(t_tree *root)
{
	int	fd;

	root = root->right;
	while (root->left)
		root = root->left;
	if (root->token->type == FILE)
	{
		fd = open(root->token->cmd[0], O_RDWR | O_CREAT | O_APPEND, 0655);
		if (fd == -1)
		{
			ft_printf ("Error opening :%s\n", root->token->cmd[0]);
			return (1);
		}
		return (fd);
	}
	return (1);
}

int	handle_append(t_tree *root, t_data data, t_env **env, t_fds *list)
{
	data.j = fd_to_out_append(root);
	if (data.j == 1)
		return (1);
	add_b_list(&list, init_list(data.j));
	if (!data.redout)
		data.outfile_fd = data.j;
	data.redout = D_RED_OUT;
	data.status = execute_cmd(root->left, data, env, list);
	if (data.status == 1)
		return (1);
	data.status = execute_cmd(root->right, data, env, list);
	if (data.status == 1)
		return (1);
	close(data.j);
	return (0);
}
