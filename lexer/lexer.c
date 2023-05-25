/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:00:28 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/25 20:43:19 by oaboulgh         ###   ########.fr       */
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
	rock->flag2 = 0;
	rock->type = -10;
	return (rock);
}

void	free_tokens(t_token **token)
{
	t_token	*tmp;

	while ((*token))
	{
		tmp = (*token);
		(*token) = (*token)->next;
		free(tmp->data);
		free(tmp);
		tmp = NULL;
	}
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

t_rock	*lex_token(t_token **token)
{
	t_rock	*rock;

	if (!token)
		return (NULL);
	rock = init_rock();
	join_arg_with_cmd(rock, *token);
	free_tokens(token);
	case_cmd_after_file(rock);
	handle_followed_red(rock);
	return (rock);
}
