/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:18:18 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/23 19:19:31 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	handle_and(t_tree *root, t_data *data, t_env **env)
{
	data->status = execute_cmd(root->left, data->infile_fd, \
		data->outfile_fd, env);
	if (data->status == 1)
		return (1);
	data->status = execute_cmd(root->right, data->infile_fd, \
		data->outfile_fd, env);
	if (data->status == 1)
		return (1);
	return (0);
}
