/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:41:58 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/23 05:56:20 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	check_root(t_tree *root)
{
	if (root->token && (root->token->type == FILE \
	|| (root->token && root->token->type == LIMITER)) \
		&& (!root->left && !root->right))
		return (1);
	return (0);
}

int	execute_cmd(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	int	k;

	k = 0;
	if (root && root->token)
		k = root->token->type;
	if (!root)
		return (0);
	if (root->token && k == PIPE && pipe_handle(root, data, env, list))
		return (1);
	else if (root->token && k == CMD && handle_command(root, data, env, list))
		return (1);
	else if (root->token && k == RED_OUT && redouthanlde(root, data, env, list))
		return (1);
	else if (root->token && k == RED_IN && handle_red_in(root, data, env, list))
		return (1);
	if (root->token && k == D_AND && handle_and(root, data, env, list))
		return (1);
	else if (root->token && k == DPIPE && d_pipe_handle(root, data, env, list))
		return (1);
	else if (root->heredoc && handle_here_doc(root, data, env, list))
		return (1);
	else if (root->token && k == D_RED_OUT && append(root, data, env, list))
		return (1);
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

void	free_fds(t_fds *list)
{
	t_fds	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->fd != 1 && tmp->fd != 0)
			close(tmp->fd);
		free(tmp);
	}
}

void	execute(t_tree *root, t_env **env)
{
	t_fds	*list;
	t_data	data;

	if (!root)
		return ;
	list = NULL;
	data.infile_fd = 0;
	data.outfile_fd = 1;
	data.type = 0;
	data.redin = 0;
	data.redout = 0;
	data.fd[0] = -2;
	data.fd[1] = -2;
	list = NULL;
	execute_cmd(root, data, env, &list);
	while (wait(NULL) != -1)
		;
	free_fds(list);
}
