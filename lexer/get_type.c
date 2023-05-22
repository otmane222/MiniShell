/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:40:46 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/22 14:17:21 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	new_rock(t_rock **rock)
{
	t_rock	*tmp;

	(*rock)->next = init_rock();
	tmp = (*rock);
	(*rock) = (*rock)->next;
	(*rock)->prev = tmp;
}

static void	get_type_assiter(t_token *t)
{
	if (ft_strncmp("<<", t->data, 4) == 0 && ft_strlen(t->data) == 2 \
		&& t->flag)
		t->type = D_RED_IN;
	else if (ft_strncmp("<", t->data, 3) == 0 && ft_strlen(t->data) == 1 \
		&& t->flag)
		t->type = RED_IN;
	else if (ft_strncmp("&&", t->data, 4) == 0 && ft_strlen(t->data) == 2 \
		&& t->flag)
		t->type = D_AND;
	else if (ft_strncmp("(", t->data, 3) == 0 && ft_strlen(t->data) == 1 \
		&& t->flag)
		t->type = O_PARENTHIS;
	else if (ft_strncmp(")", t->data, 3) == 0 && ft_strlen(t->data) == 1 \
		&& t->flag)
		t->type = C_PARENTHIS;
	else if (t->prev)
	{
		if (t->prev->type == RED_OUT || t->prev->type == RED_IN || \
		t->prev->type == D_RED_OUT)
		t->type = FILE;
		if (t->prev->type == D_RED_IN)
			t->type = LIMITER;
	}
}

static void	get_type(t_token *t)
{
	if (ft_strncmp("||", t->data, 4) == 0 && ft_strlen(t->data) == 2 \
		&& t->flag)
		t->type = DPIPE;
	else if (ft_strncmp("|", t->data, 3) == 0 && ft_strlen(t->data) == 1 \
		&& t->flag)
		t->type = PIPE;
	else if (ft_strncmp(">>", t->data, 4) == 0 && ft_strlen(t->data) == 2 \
		&& t->flag)
		t->type = D_RED_OUT;
	else if (ft_strncmp(">", t->data, 3) == 0 && ft_strlen(t->data) == 1 \
		&& t->flag)
		t->type = RED_OUT;
	else
		get_type_assiter(t);
}

void	put_type_of_tokens(t_token *tmp)
{
	while (tmp)
	{
		get_type(tmp);
		tmp = tmp->next;
	}
}
