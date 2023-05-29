/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:21:13 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/26 22:02:58 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static t_tree	*fill_right_left(t_tree *tree, t_rock *rock)
{
	rock->flag = 0;
	tree->token = rock;
	tree->left = ast_redirections(rock->prev, RED_OUT);
	tree->right = ast_pipe(rock->next);
	return (tree);
}

t_tree	*ast_pipe(t_rock *rock)
{
	t_var	var;
	t_rock	*tmp;
	t_tree	*tree;

	if (!rock || !rock->flag)
		return (NULL);
	tree = init_tree();
	get_head(&rock);
	tmp = rock;
	var.i = 0;
	while (rock && rock->flag)
	{
		skip_parenthese(&rock);
		if (rock->type == PIPE)
		{
			var.i = 1;
			break ;
		}
		rock = rock->next;
	}
	if (var.i == 0)
		return (free(tree), ast_redirections(tmp, RED_OUT));
	else if (var.i)
		return (fill_right_left(tree, rock));
	return (NULL);
}
