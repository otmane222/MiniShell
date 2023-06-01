/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:18:18 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/31 22:45:57 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	handle_and(t_tree *root, t_data data, t_env **env, t_fds *fds)
{
	data.infile_fd = 0;
	data.outfile_fd = 1;
	data.type = 0;
	data.redin = 0;
	data.redout = 0;
	data.fd[0] = -2;
	data.fd[1] = -2;
	data.status = execute_cmd(root->left, data, env, fds);
	if (data.status == 1)
		return (1);
	while (wait(NULL) != -1)
		;
	data.infile_fd = 0;
	data.outfile_fd = 1;
	data.type = 0;
	data.redin = 0;
	data.redout = 0;
	data.fd[0] = -2;
	data.fd[1] = -2;
	data.status = execute_cmd(root->right, data, env, fds);
	if (data.status == 1)
		return (1);
	return (0);
}
