/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:44:06 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/21 19:21:53 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static int	ck_pr(int a, int b)
{
	if (is_red(a))
		return (0);
	else if (is_red(b))
		return (1);
	else if (a == PIPE)
		return (2);
	else if (b == PIPE)
		return (3);
	else if (a == D_AND || a == DPIPE)
		return (4);
	else if (b == D_AND || b == DPIPE)
		return (5);
	return (-1);
}

t_tree	*case_no_next(t_rock *begin, t_rock *tok, t_rock *b, t_tree *tree)
{
	if (begin->prev->flag == 0)
	{
		b = begin->next;
		del_token(begin);
		del_token(tok);
		return (ast_parenthese(b));
	}
	else
	{
		begin->prev->flag = 0;
		tree->token = begin->prev;
		tree->left = ast_parenthese(begin->prev->prev);
		tree->right = ast_parenthese(begin);
		return (tree);
	}
}

t_tree	*case_no_perv(t_rock *begin, t_rock *tok, t_rock *b, t_tree *tree)
{
	if (tok->next->flag == 0)
	{
		b = tok->prev;
		del_token(begin);
		del_token(tok);
		return (ast_parenthese(b));
	}
	else
	{
		tok->next->flag = 0;
		tree->token = tok->next;
		tree->right = ast_parenthese(tok->next->next);
		tree->left = ast_parenthese(begin);
		return (tree);
	}
}

t_tree	*case_nothing(t_rock *begin, t_rock *tok, t_tree *tree)
{
	t_rock	*tmp;

	tmp = begin->next;
	del_token(begin);
	del_token(tok);
	free(tree);
	return (ast_parenthese(tmp));
}

t_tree	*case_both_exit(t_rock *begin, t_rock *tok, t_rock *b, t_tree *tree)
{
	int	a;
	int	g;

	a = begin->prev->type;
	g = tok->next->type;
	if (begin->prev->flag == 0)
		return (case_no_perv(begin, tok, b, tree));
	else if (tok->next->flag == 0)
		return (case_no_next(begin, tok, b, tree));
	else if (ck_pr(a, g) == 0 || ck_pr(a, g) == 2 || ck_pr(a, g) == 4)
		return (case_no_perv(begin, tok, b, tree));
	else if (ck_pr(a, g) == 1 || ck_pr(a, g) == 3 || ck_pr(a, g) == 5)
		return (case_no_next(begin, tok, b, tree));
	return (NULL);
}