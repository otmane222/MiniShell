/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:16:01 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/06 18:50:38 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	short_cut4(t_tree *root, char *tmp, char *str, t_env *env)
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

int	continue_open(t_tree *tmp2, t_tree *tmp, t_data *data, t_env *env)
{
	if (tmp2->token->type == D_RED_IN)
	{
		data->infile_fd = open_red(tmp, env, D_RED_IN);
		if (data->infile_fd == -1)
			return (1);
		data->redin = 1;
	}
	else if (tmp2->token->type == D_RED_OUT)
	{
		data->outfile_fd = open_red(tmp, env, D_RED_OUT);
		if (data->infile_fd == -1)
			return (1);
		data->redout = 1;
	}
	else if (tmp2->token->type == RED_OUT)
	{
		data->outfile_fd = open_red(tmp, env, RED_OUT);
		if (data->outfile_fd == -1)
			return (1);
		data->redout = 1;
	}
	return (0);
}

void	full_list(t_fds **list, t_data *data)
{
	if (data->infile_fd != 0)
		add_b_list(list, init_list(data->infile_fd));
	if (data->outfile_fd != 0)
		add_b_list(list, init_list(data->outfile_fd));
}

static int	fd_to_out(t_tree *root, t_env **env, t_data *data, t_fds **list)
{
	if (openfiles(root, data, *env, list))
		return (1);
	return (0);
}

int	redouthanlde(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	data.j = fd_to_out(root, env, &data, list);
	if (data.j == 1)
		return (g_exit_status = 1, 1);
	data.status = execute_cmd(root->left, data, env, list);
	if (data.status == 1)
		return (1);
	return (0);
}
