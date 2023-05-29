/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:44:29 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/29 22:31:59 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	d_pipe_handle(t_tree *root, t_data data, t_env **env, t_fds *list)
{
	data.status = execute_cmd(root->left, data, env, list);
	if (data.status == 1)
	{
		data.status = execute_cmd(root->right, data, env, list);
		if (data.status == 1)
			return (1);
	}
	return (0);
}

void	add_b_list(t_fds **lst, t_fds *neud)
{
	t_fds *temp;

	temp = *lst;
	if (lst)
	{
		if (!(*lst))
			(*lst) = neud;
		else
		{
			while (temp->next)
				temp = temp->next;
			temp->next = neud;
		}
	}
}

int	pipe_handle(t_tree *root, t_data data, t_env **env, t_fds *list)
{
	t_data	va;

	if (pipe(va.fd) == -1)
		perror ("pipe error");
	va.outfile_fd = va.fd[1];
	va.infile_fd = data.infile_fd;

	va.type = PIPE_L;
	data.status = execute_cmd(root->left, va, env, list);

	close (va.fd[1]);
	va.type = PIPE_R;
	va.outfile_fd = data.outfile_fd;
	va.infile_fd = va.fd[0];

	data.status = execute_cmd(root->right, va, env, list);
	if (data.status == 1)
		return (1);
	close (va.fd[0]);
	return (0);
}
