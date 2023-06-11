/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:33:50 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/11 13:02:27 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_valid(t_tree *root)
{
	if (root->token->is_exit)
		return (0);
	if ((root->token->prev && root->token->prev->type == PIPE) \
		|| (root->token->next && root->token->next->type == PIPE))
		return (0);
	else if (root->token->prev && \
		(root->token->prev->type == D_AND || root->token->prev->type == DPIPE))
		return (1);
	else if (root->token->next && \
		(root->token->next->type == D_AND || root->token->next->type == DPIPE))
		return (1);
	else if (!root->token->prev && !root->token->is_exit)
		return (1);
	else if (!root->token->next && !root->token->is_exit)
		return (1);
	return (0);
}

unsigned char	decimal_to_oct(int num)
{
	int	res;

	res = num % 256;
	if (res < 0)
		res += 256;
	return (res);
}

void	call_help(t_tree *root)
{
	int	status;

	status = ft_atoi(root->token->cmd[1]);
	if (is_valid(root))
	{
		write(2, "exit\n", 6);
		exit (status);
	}
	if (status > 255 || status < 0)
		g_exit_status = decimal_to_oct(status);
	else
		g_exit_status = status;
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
