/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:01:55 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/21 20:25:50 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	short_cut3(t_tree *root, char *tmp, char *str, t_env *env)
{
	if (!root->token->cmd[0])
	{
		root->token->cmd[0] = tmp;
		return (printf ("Minishell: %s: ambiguous redirect\n", \
			str), free(str), 1);
	}
	root->token->cmd[0] = expand_line(root->token->cmd[0], env);
	tmp = root->token->cmd[0];
	if (!root->token->cmd[0] || root->token->cmd[0][0] == '\0')
	{
		root->token->cmd[0] = tmp;
		return (printf ("Minishell: %s: ambiguous redirect\n", \
			str), free(str), 1);
	}
	return (0);
}

static int	fd_to_in(t_tree *root, t_env **env)
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
		if (short_cut3(root, tmp, str, *env))
			return (1);
		free(str);
		root->token->cmd[0] = deleted_q(root->token->cmd[0]);
		fd = open(root->token->cmd[0], O_RDONLY, 0655);
		if (fd == -1)
			return (printf ("minishell: %s: No such file or directory\n", \
				root->token->cmd[0]), 1);
	}
	return (fd);
}

int	handle_red_in(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	int	k;

	data.j = fd_to_in(root, env);
	if (data.j == 1)
		return (1);
	add_b_list(list, init_list(data.j));
	k = data.infile_fd;
	if (!data.redin)
		data.infile_fd = data.j;
	data.redin = RED_IN;
	data.status = execute_cmd(root->left, data, env, list);
	if (data.status == 1)
		return (1);
	data.infile_fd = k;
	data.status = execute_cmd(root->right, data, env, list);
	if (data.status == 1)
		return (1);
	close(data.j);
	return (0);
}
