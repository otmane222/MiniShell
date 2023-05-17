/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:37:15 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/03 21:29:34 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	get_type_small_call(t_token *t)
{
	if (t->prev->type == RED_OUT || t->prev->type == RED_IN || \
		t->prev->type == D_RED_OUT)
		t->type = FILE;
	if (t->prev->type == D_RED_IN)
		t->type = LIMITER;
}

void	get_type(t_token *t)
{
	if (strcmp("||", t->data) == 0)
		t->type = DPIPE;
	else if (strcmp("|", t->data) == 0)
		t->type = PIPE;
	else if (strcmp(">>", t->data) == 0)
		t->type = D_RED_OUT;
	else if (strcmp(">", t->data) == 0)
		t->type = RED_OUT;
	else if (strcmp("<<", t->data) == 0)
		t->type = D_RED_IN;
	else if (strcmp("<", t->data) == 0)
		t->type = RED_IN;
	else if (strcmp("&&", t->data) == 0)
		t->type = D_AND;
	else if (strcmp("(", t->data) == 0)
		t->type = O_PARENTHIS;
	else if (strcmp(")", t->data) == 0)
		t->type = C_PARENTHIS;
	else if (t->prev)
		get_type_small_call(t);
}

void	get_type_small_call1(t_rock *t)
{
	if (t->prev->type == RED_OUT || t->prev->type == RED_IN || \
		t->prev->type == D_RED_OUT)
		t->type = FILE;
	else if (t->prev->type == D_RED_IN)
		t->type = LIMITER;
	else
		t->type = CMD;
}

void	get_type1(t_rock *t)
{
	if (strcmp("||", t->cmd[0]) == 0)
		t->type = DPIPE;
	else if (strcmp("|", t->cmd[0]) == 0)
		t->type = PIPE;
	else if (strcmp(">>", t->cmd[0]) == 0)
		t->type = D_RED_OUT;
	else if (strcmp(">", t->cmd[0]) == 0)
		t->type = RED_OUT;
	else if (strcmp("<<", t->cmd[0]) == 0)
		t->type = D_RED_IN;
	else if (strcmp("<", t->cmd[0]) == 0)
		t->type = RED_IN;
	else if (strcmp("&&", t->cmd[0]) == 0)
		t->type = D_AND;
	else if (strcmp("(", t->cmd[0]) == 0)
		t->type = O_PARENTHIS;
	else if (strcmp(")", t->cmd[0]) == 0)
		t->type = C_PARENTHIS;
	else if (t->prev)
		get_type_small_call1(t);
	else
		t->type = CMD;
}
