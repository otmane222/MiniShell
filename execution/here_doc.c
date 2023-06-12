/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:22:21 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/10 00:32:58 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	fd_to_here_doc(t_tree *root, t_env *env)
{
	int			fd;
	t_heredoc	*tr;

	(void)env;
	tr = root->heredoc;
	root = root->heredoc->right;
	while (root && root->heredoc && root->heredoc->right)
	{
		tr = root->heredoc;
		root = root->heredoc->right;
	}
	if (root->token->type == LIMITER)
	{
		fd = open(tr->name, O_RDONLY | O_EXCL, 0655);
		if (fd == -1)
			return (1);
		return (fd);
	}
	return (1);
}

int	handle_here_doc(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	if (root->heredoc->infile_fd == -1)
		return (1);
	data.j = fd_to_here_doc(root, *env);
	if (data.j == -1)
		return (1);
	add_b_list(list, init_list(data.j));
	if (!data.redin)
		data.infile_fd = data.j;
	data.redin = D_RED_IN;
	if (execute_cmd(root->heredoc->left, data, env, list))
		return (close(data.j), 1);
	close(data.j);
	unlink(root->heredoc->name);
	return (0);
}
