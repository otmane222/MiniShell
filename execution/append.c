/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:53:48 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/23 19:11:32 by oaboulgh         ###   ########.fr       */
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
			printf ("Error opening :%s\n", root->token->cmd[0]);
			return (1);
		}
		return (fd);
	}
	return (1);
}

int	handle_append(t_tree *root, t_data *data, t_env **env)
{
	data->j = fd_to_out_append(root);
	if (data->j == -1)
		printf("Error opening file\n");
	data->status = execute_cmd(root->left, data->infile_fd, data->j, env);
	if (data->status == 1)
		return (1);
	data->status = execute_cmd(root->right, data->infile_fd, \
		data->outfile_fd, env);
	if (data->status == 1)
		return (1);
	return (0);
}
