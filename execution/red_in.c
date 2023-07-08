/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:01:55 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/06 18:49:58 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	update_root(t_tree **root)
{
	while ((*root))
	{
		if ((*root)->left)
			(*root) = (*root)->left;
		else if ((*root)->heredoc)
		{
			if ((*root)->heredoc->left)
				(*root) = (*root)->heredoc->left;
		}
		else
			break ;
	}
}

static int	fd_to_in(t_tree *root, t_env **env, t_data *data, t_fds **list)
{
	(void)env;
	if (openfiles(root, data, *env, list))
		return (1);
	return (0);
}

int	handle_red_in(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	data.j = fd_to_in(root, env, &data, list);
	if (data.j == 1)
		return (g_exit_status = 1, 1);
	data.status = execute_cmd(root->left, data, env, list);
	if (data.status == 1)
		return (1);
	return (0);
}
