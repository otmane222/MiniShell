/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:53:48 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/21 20:25:37 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	short_cut2(t_tree *root, char *tmp, char *str, t_env *env)
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

static int	file_call(t_tree *root, t_env *env)
{
	char	*str;
	char	*tmp;
	int		fd;

	tmp = root->token->cmd[0];
	str = ft_strdup(root->token->cmd[0]);
	root->token->cmd[0] = handle_wildcard_char(root->token->cmd[0]);
	if (short_cut2(root, tmp, str, env))
		return (1);
	free(str);
	root->token->cmd[0] = deleted_q(root->token->cmd[0]);
	fd = open(root->token->cmd[0], O_RDWR | O_CREAT | O_APPEND, 0655);
	if (fd == -1)
	{
		printf ("Minishell: %s: No such file or directory\n", \
			root->token->cmd[0]);
		return (1);
	}
	return (fd);
	return (1);
}

static int	fd_to_out_append(t_tree *root, t_env *env)
{
	root = root->right;
	while (root->left)
		root = root->left;
	if (root && root->token->type == FILE)
		return (file_call(root, env));
	return (1);
}

int	append(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	data.j = fd_to_out_append(root, *env);
	if (data.j == 1)
		return (1);
	add_b_list(list, init_list(data.j));
	if (!data.redout)
		data.outfile_fd = data.j;
	data.redout = D_RED_OUT;
	data.status = execute_cmd(root->left, data, env, list);
	if (data.status == 1)
		return (1);
	data.status = execute_cmd(root->right, data, env, list);
	if (data.status == 1)
		return (1);
	close(data.j);
	return (0);
}
