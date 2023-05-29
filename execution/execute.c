/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:41:58 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/29 22:25:19 by oaboulgh         ###   ########.fr       */
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

int	execute_cmd(t_tree *root, t_data data, t_env **env, t_fds *list)
{
	if (!root || check_root(root))
		return (0);
	if (root->token && root->token->type == PIPE && pipe_handle(root, data, env, list))
		return (1);
	else if (root->token && root->token->type == CMD && handle_command(root, data, env, list))
		return (1);
	else if (root && root->token->type == RED_OUT && red_out_hanlde(root, data, env, list))
		return (1);
	else if (root && root->token->type == RED_IN && handle_red_in(root, data, env, list))
		return (1);
	else if (root->token && root->token->type == D_AND && handle_and(root, data, env, list))
		return (1);
	else if (root->token && root->token->type == DPIPE && d_pipe_handle(root, data, env, list))
		return (1);
	// else if (root && root->token->type == D_RED_OUT && handle_append(root, data, env))
	// 	return (1);
	// else if (root && root->token->type == D_RED_IN && handle_here_doc(root, data, env))
	// 	return (1);
	return (0);
}

t_fds	*init_list(int fd)
{
	t_fds	*list;

	list = malloc(sizeof(t_fds));
	if (!list)
		return (NULL);
	list->fd = fd;
	list->next = NULL;
	return (list);
}

void	free_fds(t_fds *list, int k)
{
	while (list)
	{
		if (list->fd != k)
			close(list->fd);
		printf("---%d---\n", list->fd);
		list = list->next;
	}
}

void	execute(t_tree *root, t_env **env)
{
	t_fds	*list;
	t_data	data;

	data.infile_fd = 0;
	data.outfile_fd = 1;
	data.fd[0] = -2;
	data.fd[1] = -2;
	list = NULL;
	if (execute_cmd(root, data, env, list) == 1)
	{
		// free_fds(list);
		return ;
	}
	while (wait(NULL) != -1)
		;
}
