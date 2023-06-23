/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_array_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:17:17 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/21 23:57:19 by oaboulgh         ###   ########.fr       */
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
	free(rock->arr);
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

static void	helpful_call2(t_rock *tmp, t_rock *rock, int *num, t_var var)
{
	while (tmp->cmd[var.i])
	{
		num[var.i] = tmp->arr[var.i];
		var.i++;
	}
	while (rock->cmd[var.j])
	{
		num[var.i] = rock->arr[var.j];
		var.i++;
		var.j++;
	}
	free(tmp->arr);
	tmp->arr = num;
	num[var.i] = 0;
}

void	join_2d_arrs(t_rock *rock, t_rock *tmp)
{
	char	**arr;
	int		*num;
	t_var	var;

	var.i = 0;
	var.j = 0;
	while (rock->cmd[var.i])
		var.i++;
	while (tmp->cmd[var.j])
		var.j++;
	num = malloc(sizeof(int) * (var.i + var.j + 1));
	if (!num)
		return ;
	arr = malloc(sizeof(char *) * (var.i + var.j + 1));
	if (!arr)
		return ;
	var.i = 0;
	var.j = 0;
	helpful_call(tmp, rock, arr, var);
	helpful_call2(tmp, rock, num, var);
	del_rock(rock);
	free_2dd(tmp->cmd);
	tmp->cmd = arr;
}
