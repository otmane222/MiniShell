/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:01:55 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/25 13:45:18 by oaboulgh         ###   ########.fr       */
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
			printf ("Error opening :%s\n", root->token->cmd[0]);
			return (-1);
		}
		return (fd);
	}
	return (0);
}

int	handle_red_in(t_tree *root, t_data *data, t_env **env)
{
	data->j = fd_to_in(root);
	if (data->j == -1)
		return (1);
	if (data->j == -1)
		return (printf("Error opening file\n"), 1);
	data->status = execute_cmd(root->left, data->j, data->outfile_fd, env);
	if (data->status == 1)
		return (1);
	data->status = execute_cmd(root->right, data->infile_fd, \
		data->outfile_fd, env);
	if (data->status == 1)
		return (1);
	return (0);
}
