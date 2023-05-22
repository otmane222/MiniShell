/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:21:19 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/22 17:21:21 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static t_tree	*fill_right_left(t_tree *tree, t_rock *rock)
{
	rock->flag = 0;
	tree->token = rock;
	tree->left = ast_redirections(rock->prev);
	tree->right = ast_redirections(rock->next);
	return (tree);
}

static t_tree	*case_file(t_rock *tmp, t_tree *tree)
{
	if (!tmp)
		return (NULL);
	if (tmp->next)
	{
		if (tmp->next->flag && tmp->type == FILE)
		{
			tree->left = init_tree();
			tree->left->token = tmp;
			tree->token = tmp->next;
			return (tree);
		}
	}
	tree->token = tmp;
	return (tree);
}

int	is_red(int a)
{
	if (a == D_RED_OUT || a == RED_IN || a == RED_OUT || a == D_RED_IN)
		return (1);
	return (0);
}

t_tree	*ast_redirections(t_rock *tok)
{
	t_var	var;
	t_rock	*tmp;
	t_tree	*tree;

	tree = init_tree();
	get_head(&tok);
	if (!tok)
		return (NULL);
	tmp = tok;
	var.i = 0;
	while (tok && tok->flag)
	{
		if (is_red(tok->type))
		{
			var.i = 1;
			break ;
		}
		tok = tok->next;
	}
	if (var.i == 0)
		return (case_file(tmp, tree));
	else if (var.i)
		return (fill_right_left(tree, tok));
	return (NULL);
}
