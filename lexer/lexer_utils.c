/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:29:25 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/27 04:04:08 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_kind(int a)
{
	if (a == PIPE || a == DPIPE || a == D_AND || a == O_PARENTHIS || \
		a == C_PARENTHIS)
		return (1);
	if (a == D_RED_OUT || a == RED_IN || a == RED_OUT || a == D_RED_IN)
		return (2);
	return (0);
}

void	flag_cmd(t_rock *rock)
{
	if (!rock)
		return ;
	while (rock && rock->type != D_AND && rock->type != DPIPE)
	{
		if (rock->type == CMD)
		{
			rock->is_last = 1;
			return ;
		}
		rock = rock->prev;
	}
}

int	check_parsing(t_rock *rock)
{
	while (rock)
	{
		if (rock->type == C_PARENTHIS && rock->next && rock->next->type == CMD)
			return (ft_printf("minishell: syntax error near unexpected token"), \
				ft_printf(" `%s'\n", rock->next->cmd[0]), 1);
		rock = rock->next;
	}
	return (0);
}
