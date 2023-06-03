/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:33:50 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/03 21:47:05 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_valid(t_tree *root)
{
	if ((root->token->prev && root->token->prev->type == PIPE) \
		|| (root->token->next && root->token->next->type == PIPE))
		return (0);
	else if (root->token->prev && \
		(root->token->prev->type == D_AND || root->token->prev->type == DPIPE))
		return (1);
	else if (root->token->next && \
		(root->token->next->type == D_AND || root->token->next->type == DPIPE))
		return (1);
	else if (!root->token->prev && !root->token->flag2)
		return (1);
	else if (!root->token->next && !root->token->flag2)
		return (1);
	return (0);
}

void	call_help(t_tree *root)
{
	int	status;

	if (is_valid(root))
	{
		write(2, "exit\n", 6);
		status = ft_atoi(root->token->cmd[1]);
		exit (status);
	}
}

int	ft_exit(t_tree *root)
{
	int	i;

	i = 0;
	while (root->token->cmd[i])
		i++;
	if (i > 2)
	{
		i = 0;
		while (root->token->cmd[1][i] >= '0' && root->token->cmd[1][i] <= '9')
			i++;
		if (!root->token->cmd[1][i])
			return (write(2, "exit\nminishell: exit: too many arguments\n", \
				42), 1);
	}
	if (root && root->token->cmd && root->token->cmd[1])
		call_help(root);
	else if (is_valid(root))
	{
		write(2, "exit\n", 6);
		exit (0);
	}
	return (1);
}
