/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:52:08 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/21 19:09:10 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	del_token(t_rock *tok)
{
	t_rock	*tmp;
	t_rock	*tmp2;

	if (!tok)
		return ;
	tmp = tok->next;
	tmp2 = tok->prev;
	free_2dd(tok->cmd);
	free(tok);
	tok = NULL;
	if (tmp)
		tmp->prev = tmp2;
	if (tmp2)
		tmp2->next = tmp;
}

t_tree	*init_tree(void)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->left = NULL;
	tree->right = NULL;
	tree->token = NULL;
	return (tree);
}

void	init_var_2(t_var **var)
{
	(*var) = malloc(sizeof(t_var));
	(*var)->i = 0;
	(*var)->j = 0;
	(*var)->check = 1;
	(*var)->status = 0;
	(*var)->counter = 0;
	(*var)->qoutes_flag = 0;
	(*var)->start = 0;
	(*var)->end = 0;
}

void	get_head(t_rock **head)
{
	if (!(*head))
		return ;
	if (!(*head)->prev)
		return ;
	while ((*head)->prev)
	{
		if ((*head)->prev->flag == 0)
			break ;
		(*head) = (*head)->prev;
	}
}

t_tree	*ast_tokenes(t_rock *rock)
{
	t_tree	*root;

	root = ast_parenthese(rock);
	return (root);
}
