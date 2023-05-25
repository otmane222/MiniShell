/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:44:29 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/25 11:41:13 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	d_pipe_handle(t_tree *root, t_data *data, t_env **env)
{
	data->status = execute_cmd(root->left, data->infile_fd, \
		data->outfile_fd, env);
	if (data->status == 1)
	{
		data->status = execute_cmd(root->right, data->infile_fd, \
			data->outfile_fd, env);
		if (data->status == 1)
			return (1);
	}
	return (0);
}

int	pipe_handle(t_tree *root, t_data *data, t_env **env)
{
	if (pipe(data->fd) == -1)
		perror ("pipe error");
	data->status = execute_cmd(root->left, data->infile_fd, data->fd[1], env);
	if (data->status == 1)
		return (1);
	close (data->fd[1]);
	data->status = execute_cmd(root->right, data->fd[0], data->outfile_fd, env);
	if (data->status == 1)
		return (1);
	close (data->fd[0]);
	return (0);
}
