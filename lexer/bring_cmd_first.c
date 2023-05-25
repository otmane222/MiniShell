/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bring_cmd_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:52:14 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/25 18:19:28 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	to_do(t_rock *tmp3, t_rock *tmp2, t_rock **rock, t_rock *tmp)
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

static void	fix(t_rock **rock)
{
	t_rock	*tmp;
	t_rock	*tmp2;
	t_rock	*tmp3;

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
				if (!tmp || (tmp->type != FILE && !is_red2(tmp->type)))
				{
					to_do(tmp3, tmp2, rock, tmp);
					return ;
				}
				if (tmp->type == CMD)
					break ;
			}
		}
	}
}

static void	get_cmd(t_rock *rock, t_rock *tmp)
{
	t_rock	*temp;

	if (!rock || !rock->next || rock->next->type != CMD)
		return ;
	temp = (rock)->next;
	join_2d_arrs(temp, tmp);
}

void	case_of_arg_after_file(t_rock *rock)
{
	t_rock	*tmp;

	tmp = NULL;
	while (rock)
	{
		if (rock->type == CMD)
			tmp = rock;
		else if (tmp && (rock->type == FILE || rock->type == LIMITER))
		{
			get_cmd(rock, tmp);
			if (!rock)
				break ;
		}
		else if (rock->type == PIPE || rock->type == DPIPE || \
			rock->type == D_AND || rock->type == O_PARENTHIS)
			tmp = NULL;
		rock = rock->next;
	}
}

void	case_cmd_after_file(t_rock *rock)
{
	t_rock	*tmp;

	case_of_arg_after_file(rock);
	get_head1(&rock);
	tmp = rock;
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
	rock = tmp;
	get_head1(&rock);
}
