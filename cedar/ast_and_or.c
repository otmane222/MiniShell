/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_and_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:20:58 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/22 22:30:39 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static t_tree	*fill_right_left(t_tree *tree, t_rock *rock)
{
	rock->flag = 0;
	tree->token = rock;
	tree->left = ast_and(rock->prev);
	tree->right = ast_and(rock->next);
	return (tree);
}

static t_tree	*fill_right_left1(t_tree *tree, t_rock *rock)
{
	rock->flag = 0;
	tree->token = rock;
	tree->left = ast_or(rock->prev);
	tree->right = ast_or(rock->next);
	return (tree);
}

void	skip_parenthese(t_rock **rock)
{
	int	i;

	i = 0;
	if ((*rock)->type == O_PARENTHIS)
	{
		while ((*rock) && (*rock)->flag)
		{
			if ((*rock)->type == O_PARENTHIS)
				i++;
			else if ((*rock)->type == C_PARENTHIS)
			{
				i--;
				if (i == 0)
					break ;
			}
			*rock = (*rock)->next;
		}
	}
}

t_tree	*ast_and(t_rock *rock)
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
		skip_parenthese(&rock);
		if (rock->type == D_AND)
		{
			var.i = 1;
			break ;
		}
		rock = rock->next;
	}
	if (var.i == 0)
		return (free(tree), ast_or(tmp));
	else if (var.i == 1)
		return (fill_right_left(tree, rock));
	return (NULL);
}

t_tree	*ast_or(t_rock *rock)
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
		skip_parenthese(&rock);
		if (rock->type == DPIPE)
		{
			var.i = 1;
			break ;
		}
		rock = rock->next;
	}
	if (var.i == 0)
		return (free(tree), ast_pipe(tmp));
	else if (var.i == 1)
		return (fill_right_left1(tree, rock));
	return (NULL);
}
