/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:31:07 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/04 16:49:40 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	fix(t_rock **rock)
{
	t_rock	*tmp;
	t_rock	*tmp2;
	t_rock	*tmp3;
	t_rock	*tmp4;

	tmp = (*rock);
	if (tmp->next)
	{
		if (tmp->next->type == CMD)
		{
			tmp2 = tmp->next;
			while (tmp)
			{
				tmp3 = tmp;
				tmp = tmp->prev;
				if (!tmp || tmp->type == CMD || tmp->type == PIPE || \
				tmp->type == D_AND || tmp->type == DPIPE \
					|| tmp->type == O_PARENTHIS)
				{
					if (!tmp || tmp->type == PIPE || tmp->type == D_AND || \
						tmp->type == DPIPE || tmp->type == O_PARENTHIS)
					{
						tmp3->prev = tmp2;
						(*rock)->next = tmp2->next;
						if (tmp2->next)
							tmp2->next->prev = (*rock);
						tmp2->next = tmp3;
						tmp2->prev = tmp;
						if (tmp && tmp->next)
							tmp->next = tmp2;
					}
					return ;
				}
			}
		}
	}
}

void	case_cmd_after_file(t_rock *rock)
{
	get_head1(&rock);
	while (rock)
	{
		if (rock->type == FILE || rock->type == LIMITER)
		{
			fix(&rock);
			if (!rock)
				break ;
		}
		rock = rock->next;
	}
}

void	free_2dd(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

void	del_rock3(t_rock *rock)
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

void	join_2d_arrs(t_rock *rock, t_rock *tmp, t_var var)
{
	char	**arr;

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
	del_rock3(rock);
	free_2dd(tmp->cmd);
	tmp->cmd = arr;
}

void	get_cmd(t_rock *rock, t_rock *tmp)
{
	t_rock	*temp;
	t_var	var;

	if (!rock || !rock->next || rock->next->type != CMD)
		return ;
	temp = (rock)->next;
	join_2d_arrs(temp, tmp, var);
}

void	case_of_arg_after_file(t_rock *rock)
{
	t_rock	*tmp;

	while (rock)
	{
		if (rock->type == CMD)
			tmp = rock;
		if (rock->type == FILE || rock->type == LIMITER)
		{
			get_cmd(rock, tmp);
			if (!rock)
				break ;
		}
		rock = rock->next;
	}
}
