/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:41:58 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/25 16:36:48 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	check_root(t_tree *root)
{
	if (root->token && (root->token->type == FILE || (root->token && root->token->type == LIMITER)) \
		&& (!root->left && !root->right))
		return (1);
	return (0);
}

int	execute_cmd(t_tree *root, int infile_fd, int outfile_fd, t_env **env)
{
	t_data	data;

	data.infile_fd = infile_fd;
	data.outfile_fd = outfile_fd;
	if (!root || check_root(root))
		return (0);
	if (root->token && root->token->type == PIPE && pipe_handle(root, &data, env))
		return (1);
	else if (root && root->token->type == RED_OUT && red_out_hanlde(root, data, env))
		return (1);
	else if (root && root->token->type == D_RED_OUT && handle_append(root, &data, env))
		return (1);
	else if (root && root->token->type == RED_IN && handle_red_in(root, &data, env))
		return (1);
	else if (root->token && root->token->type == DPIPE && d_pipe_handle(root, &data, env))
		return (1);
	else if (root->token && root->token->type == D_AND && handle_and(root, &data, env))
		return (1);
	else if (root && root->token->type == D_RED_IN && handle_here_doc(root, data, env))
		return (1);
	else if (root->token && root->token->type == CMD && handle_command(root, &data, env))
		return (1);
	return (0);
}

void	execute(t_tree *root, t_env **env)
{
	if (execute_cmd(root, 0, 1, env) == 1)
		return ;
}
