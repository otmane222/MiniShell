/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parethese.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:09:41 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/21 19:32:43 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static int	parenthese_call(t_rock *rock, t_rock **begin, t_var *var)
{
	if (rock->type == O_PARENTHIS)
	{
		if (!begin || !*begin)
			*begin = rock;
		if (var->i == -1)
			var->i++;
		var->i++;
	}
	else if (rock->type == C_PARENTHIS)
	{
		var->i--;
		if (var->i == 0)
			return (0);
	}
	return (1);
}

static t_tree	*cases(t_rock *begin, t_rock *tok, t_rock *b, t_tree *tree)
{
	if (!begin->prev && !tok->next)
	{
		return (case_nothing(begin, tok, tree));
	}
	else if (begin->prev && !tok->next)
	{
		return (case_no_next(begin, tok, b, tree));
	}
	else if (!begin->prev && tok->next)
		return (case_no_perv(begin, tok, b, tree));
	else if (begin->prev && tok->next)
		return (case_both_exit(begin, tok, b, tree));
	printf("hela\n");
	return (NULL);
}

t_tree	*ast_parenthese(t_rock *rock)
{
	t_var	var;
	t_rock	*begin;
	t_rock	*b;
	t_tree	*tree;

	if (!rock)
		return (NULL);
	tree = init_tree();
	var.i = -1;
	begin = NULL;
	get_head(&rock);
	b = rock;
	while (rock && rock->flag)
	{
		if (!parenthese_call(rock, &begin, &var))
			break ;
		rock = rock->next;
	}
	if (var.i == -1)
	{
		rock = b;
		return (free(tree), ast_and_or(rock));
	}
	else if (var.i == 0)
		return (cases(begin, rock, b, tree));
	return (NULL);
}