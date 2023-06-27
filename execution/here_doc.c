/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:22:21 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/26 18:39:58 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	small_call(t_tree **tmp, t_tree **tmp2, t_tree **root)
{
	*tmp2 = (*root);
	(*root) = (*root)->right;
	(*tmp) = (*root);
	if ((*tmp)->left)
		(*tmp) = (*tmp)->left;
}

int	openfiles(t_tree *root, t_data *data, t_env *env, t_fds **list)
{
	t_tree	*tmp;
	t_tree	*tmp2;
	int		fd;

	fd = 0;
	tmp = root;
	while (root->right && is_red(root->token->type))
	{
		small_call(&tmp, &tmp2, &root);
		if (tmp2->token->type == RED_IN)
		{
			data->infile_fd = open_red(tmp, env, RED_IN);
			if (data->infile_fd == -1)
				return (1);
			data->redin = 1;
		}
		else
			if (continue_open(tmp2, tmp, data, env))
				return (1);
		full_list(list, data);
	}
	return (0);
}

int	fd_to_here_doc(t_tree *root, t_data *data, t_env *env, t_fds **list)
{
	if (openfiles(root, data, env, list))
		return (1);
	return (0);
}

int	handle_here_doc(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	data.j = fd_to_here_doc(root, &data, *env, list);
	if (data.j == -1)
		return (1);
	if (execute_cmd(root->left, data, env, list))
		return (1);
	unlink(root->token->cmd[0]);
	return (0);
}
