/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:16:01 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/24 19:00:04 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// static int	fd_to_out(t_tree *root)
// {
// 	int	fd;

// 	root = root->right;
// 	while (root->left)
// 		root = root->left;
// 	if (root && root->token->type == FILE)
// 	{
// 		fd = open(root->token->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0655);
// 		if (fd == -1)
// 		{
// 			printf ("Error opening :%s\n", root->token->cmd[0]);
// 			return (1);
// 		}
// 		return (fd);
// 	}
// 	return (0);
// }

int	red_out_hanlde(t_tree *root, t_data data, t_env **env)
{
	data.j = open(root->red->token->next->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0655);
	if (data.j == -1)
	{
		printf ("Error opening :%s\n", root->token->cmd[0]);
		return (1);
	}
	if (data.j == -1)
		printf("Error opening file\n");
	data.status = execute_cmd(root->left, data.infile_fd, data.j, env);
	if (data.status == 1)
		return (1);
	data.status = execute_cmd(root->red->right, data.infile_fd, \
		data.outfile_fd, env);
	if (data.status == 1)
		return (1);
	return (0);
}
