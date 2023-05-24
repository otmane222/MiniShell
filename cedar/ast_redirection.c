/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:21:19 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/24 15:41:10 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static t_tree	*fill_right_left(t_tree *tree, t_rock *rock)
{
	rock->flag = 0;
	tree->red = malloc(sizeof(t_red));
	if (!tree->red)
		return (NULL);
	tree->red->token = NULL;
	tree->red->right = NULL;
	tree->red->token = rock;
	tree->left = ast_redirections(rock->prev);
	tree->red->right = ast_redirections(rock->next);
	return (tree);
}

t_rock	*get_tail(t_rock *rock)
{
	if (!rock)
		return (NULL);
	if (!rock->next)
		return (rock);
	while (rock->next && rock->next->flag)
		rock = rock->next;
	return (rock);
}

static t_tree	*case_file(t_rock *tmp, t_tree *tree)
{
	t_rock	*tmp2;
	t_rock	*tmp3;

	tmp3 = get_tail(tmp);
	if (tmp->type == O_PARENTHIS)
	{
		tmp2 = tmp->next;
		tmp2->flag2 = 1;
		del_token(tmp);
		del_token(tmp3);
		free(tree);
		return (ast_and(tmp2));
	}
	else
	{
		tree->token = tmp;
		tree->token->flag = 0;
		return (tree);
	}
}

int	is_red(int a)
{
	if (a == D_RED_OUT || a == RED_IN || a == RED_OUT || a == D_RED_IN)
		return (1);
	return (0);
}

t_tree	*ast_redirections(t_rock *rock)
{
	t_var	var;
	t_rock	*tmp;
	t_tree	*tree;

	tree = init_tree();
	get_head(&rock);
	if (!rock)
		return (NULL);
	tmp = rock;
	var.i = 0;
	while (rock && rock->flag)
	{
		skip_parenthese(&rock);
		if (is_red(rock->type))
		{
			var.i = 1;
			break ;
		}
		rock = rock->next;
	}
	if (var.i == 0)
		return (case_file(tmp, tree));
	else if (var.i)
		return (fill_right_left(tree, rock));
	return (NULL);
}
