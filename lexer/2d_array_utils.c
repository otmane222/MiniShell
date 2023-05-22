/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_array_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:17:17 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/22 12:11:37 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_red2(int a)
{
	if (a == D_RED_OUT || a == RED_IN || a == RED_OUT || a == D_RED_IN)
		return (1);
	return (0);
}

void	del_rock(t_rock *rock)
{
	t_rock	*tmp;
	t_rock	*tmp2;

	if (!rock)
		return ;
	tmp = rock->next;
	tmp2 = rock->prev;
	free_2dd(rock->cmd);
	free(rock);
	rock = NULL;
	if (tmp)
		tmp->prev = tmp2;
	if (tmp2)
		tmp2->next = tmp;
}

static void	helpful_call(t_rock *tmp, t_rock *rock, char **arr, t_var var)
{
	while (tmp->cmd[var.i])
	{
		arr[var.i] = ft_strdup(tmp->cmd[var.i]);
		var.i++;
	}
	while (rock->cmd[var.j])
	{
		arr[var.i] = ft_strdup(rock->cmd[var.j]);
		var.i++;
		var.j++;
	}
	arr[var.i] = NULL;
}

void	join_2d_arrs(t_rock *rock, t_rock *tmp)
{
	char	**arr;
	t_var	var;

	var.i = 0;
	var.j = 0;
	while (rock->cmd[var.i])
		var.i++;
	while (tmp->cmd[var.j])
		var.j++;
	arr = malloc(sizeof(char *) * (var.i + var.j + 1));
	if (!arr)
		return ;
	var.i = 0;
	var.j = 0;
	helpful_call(tmp, rock, arr, var);
	del_rock(rock);
	free_2dd(tmp->cmd);
	tmp->cmd = arr;
}
