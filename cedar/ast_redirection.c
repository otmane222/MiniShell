/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:21:19 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/31 18:42:19 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static t_tree	*fill_right_left(t_tree *tree, t_rock *rock, int flag)
{
	rock->flag = 0;
	tree->token = rock;
	tree->left = ast_redirections(rock->prev, flag);
	tree->right = ast_redirections(rock->next, flag);
	return (tree);
}

t_rock	*get_last(t_rock *rock)
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

	tmp3 = get_last(tmp);
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

void	get_tail(t_rock **head)
{
	if (!(*head) || !(*head)->flag)
		return ;
	if (!(*head)->next || !(*head)->next->flag)
		return ;
	while ((*head)->next)
	{
		if ((*head)->next->flag == 0)
			break ;
		(*head) = (*head)->next;
	}
}

void	skip_parenthese1(t_rock **rock)
{
	int	i;

	i = 0;
	if ((*rock)->type == C_PARENTHIS)
	{
		while ((*rock) && (*rock)->flag)
		{
			if ((*rock)->type == C_PARENTHIS)
				i++;
			else if ((*rock)->type == O_PARENTHIS)
			{
				i--;
				if (i == 0)
					break ;
			}
			*rock = (*rock)->prev;
		}
	}
}

t_tree	*ast_redirections(t_rock *rock, int flag)
{
	t_var	var;
	t_rock	*tmp;
	t_tree	*tree;

	if (!rock || !rock->flag)
		return (NULL);
	tree = init_tree();
	get_head(&rock);
	tmp = rock;
	get_tail(&rock);
	var.i = 0;
	while (rock && rock->flag)
	{
		skip_parenthese1(&rock);
		if (is_red(rock->type))
		{
			var.i = 1;
			break ;
		}
		rock = rock->prev;
	}
	if (var.i == 0)
		return (case_file(tmp, tree));
	else if (var.i)
		return (fill_right_left(tree, rock, flag));
	return (NULL);
}
