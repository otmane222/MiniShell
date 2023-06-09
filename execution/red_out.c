/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:16:01 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/09 14:48:55 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	fd_to_out(t_tree *root, t_env **env)
{
	int		fd;
	char	*str;
	char	*tmp;

	root = root->right;
	while (root->left)
		root = root->left;
	fd = 1;
	if (root && root->token->type == FILE)
	{
		tmp = root->token->cmd[0];
		str = ft_strdup(root->token->cmd[0]);
		root->token->cmd[0] = handle_wildcard_char(root->token->cmd[0]);
		if (!root->token->cmd[0])
		{
			root->token->cmd[0] = tmp;
			return (printf ("Minishell: %s: ambiguous redirect\n", \
				str), free(str), 1);
		}
		root->token->cmd[0] = expand_line(root->token->cmd[0], *env);
		tmp = root->token->cmd[0];
		if (root->token->cmd[0][0] == '\0')
		{
			root->token->cmd[0] = tmp;
			return (printf ("Minishell: %s: ambiguous redirect\n", \
				str), free(str), 1);
		}
		free(str);
		root->token->cmd[0] = deleted_q(root->token->cmd[0]);
		fd = open(root->token->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0655);
		if (fd == -1)
		{
			printf ("Minishell: %s: No such file or directory\n", \
				root->token->cmd[0]);
			return (1);
		}
		return (fd);
	}
	return (1);
}

int	red_out_hanlde(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	data.j = fd_to_out(root, env);
	if (data.j == 1)
		return (1);
	add_b_list(list, init_list(data.j));
	if (!data.redout || data.redout == -19)
		data.outfile_fd = data.j;
	if (!root->token->red_p)
		data.redout = RED_OUT;
	else
		data.redout = -19;
	data.status = execute_cmd(root->left, data, env, list);
	if (data.status == 1)
		return (close(data.j), 1);
	close(data.j);
	return (0);
}
