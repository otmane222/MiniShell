/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:11:32 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/23 01:31:26 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	child_execute(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	char	**paths;
	char	*cmd;

	handle_files(&data);
	paths = ft_split(ft_getenv("PATH", *env), ':');
	case_directory(root->token->cmd[0]);
	cmd = check_path(paths, root->token->cmd[0]);
	execute_execve(cmd, root->token->cmd, *env, *list);
}
