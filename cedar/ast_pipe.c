/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:22:55 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/21 18:55:54 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static t_tree	*fill_right_left(t_tree *tree, t_rock *rock)
{
	rock->flag = 0;
	tree->token = rock;
	tree->left = ast_pipe(rock->prev);
	tree->right = ast_pipe(rock->next);
	return (tree);
}

t_tree	*ast_pipe(t_rock *tok)
{
	t_var	var;
	t_rock	*tmp;
	t_tree	*tree;

	tree = init_tree();
	get_head(&tok);
	tmp = tok;
	var.i = 0;
	while (tok && tok->flag)
	{
		if (tok->type == PIPE)
		{
			var.i = 1;
			break ;
		}
		tok = tok->next;
	}
	if (var.i == 0)
		return (free(tree), ast_redirections(tmp));
	else if (var.i)
		return (fill_right_left(tree, tok));
	return (NULL);
}