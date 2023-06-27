/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:18:18 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/27 03:45:57 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	handle_and(t_tree *root, t_data data, t_env **env, t_fds **fds)
{
	data.status = execute_cmd(root->left, data, env, fds);
	if (data.status == 1)
		return (1);
	while (wait(NULL) != -1)
		;
	data.status = execute_cmd(root->right, data, env, fds);
	if (data.status == 1)
		return (1);
	return (0);
}
