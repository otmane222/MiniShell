/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:00:28 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/23 11:54:16 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_rock	*init_rock(void)
{
	t_rock	*rock;

	rock = malloc(sizeof(t_rock));
	if (!rock)
		return (NULL);
	rock->cmd = NULL;
	rock->next = NULL;
	rock->prev = NULL;
	rock->flag = 1;
	rock->is_exit = 0;
	rock->red_p = 0;
	rock->arr = NULL;
	rock->expand = 1;
	rock->is_last = 0;
	rock->type = -10;
	return (rock);
}

void	get_head1(t_rock **head)
{
	if (!(*head))
		return ;
	if (!(*head)->prev)
		return ;
	while ((*head)->prev)
		(*head) = (*head)->prev;
}

void	swap_token_char(t_rock **a, t_rock **b)
{
	char	*tmp;

	if (!(*b) || !(*a))
		return ;
	if ((*a)->next)
		if ((*a)->next->type == C_PARENTHIS)
			return ;
	tmp = (*a)->cmd[0];
	(*a)->cmd[0] = (*b)->cmd[0];
	(*b)->cmd[0] = tmp;
}

void	flag_last_cmds(t_rock *rock)
{
	get_head1(&rock);
	while (rock)
	{
		if (!rock->next)
			flag_cmd(rock);
		if (rock->type == D_AND || rock->type == DPIPE)
			flag_cmd(rock->prev);
		rock = rock->next;
	}
}

t_rock	*lex_token(t_token **token)
{
	t_rock	*rock;

	if (!token)
		return (NULL);
	rock = init_rock();
	join_arg_with_cmd(rock, *token);
	free_tokens(token);
	case_cmd_after_file(rock);
	flag_last_cmds(rock);
	return (rock);
}
