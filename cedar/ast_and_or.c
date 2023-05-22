/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_and_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:11:13 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/21 19:18:40 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static t_tree	*fill_right_left(t_tree *tree, t_rock *rock)
{
	rock->flag = 0;
	tree->token = rock;
	tree->left = ast_and_or(rock->prev);
	tree->right = ast_and_or(rock->next);
	return (tree);
}

t_tree	*ast_and_or(t_rock *rock)
{
	t_rock	*tmp;
	t_tree	*tree;
	t_var	var;

	if (!rock)
		return (NULL);
	get_head(&rock);
	tmp = rock;
	tree = init_tree();
	var.i = 0;
	while (rock && rock->flag)
	{
		if (rock->type == D_AND || rock->type == DPIPE)
		{
			var.i = 1;
			break ;
		}
		rock = rock->next;
	}
	if (var.i == 0)
		return (free(tree), ast_pipe(tmp));
	else if (var.i == 1)
		return (fill_right_left(tree, rock));
	return (NULL);
}
