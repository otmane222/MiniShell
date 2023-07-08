/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:11:32 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/07 15:53:58 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	child_execute(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	char	**paths;
	char	*cmd;

	if (built_in(root->token->cmd[0], root->token->cmd, env))
	{
		runnig_cmd(0);
		run_built_in(root, data, env);
		exit (g_exit_status);
	}
	handle_files(&data);
	paths = ft_split(ft_getenv("PATH", *env), ':');
	case_directory(root->token->cmd[0]);
	cmd = check_path(paths, root->token->cmd[0]);
	execute_execve(cmd, root->token->cmd, *env, *list);
}

int	and_or(int a)
{
	if (a == D_AND || a == DPIPE)
		return (1);
	else
		return (0);
}

int	valid_in_parent(t_tree *root)
{
	if (!root->token->next && !root->token->prev)
		return (1);
	else if (!root->token->prev && root->token->next \
		&& and_or(root->token->next->type))
		return (1);
	else if (!root->token->next && root->token->prev \
		&& and_or(root->token->prev->type))
		return (1);
	else if (root->token->next && root->token->prev \
		&& and_or(root->token->prev->type) && and_or(root->token->next->type))
		return (1);
	return (0);
}
