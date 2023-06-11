/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:21:30 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/10 22:14:36 by oaboulgh         ###   ########.fr       */
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
	free(tok->arr);
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
	tree->heredoc = NULL;
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
	if (!(*head) || !(*head)->flag)
		return ;
	if (!(*head)->prev || !(*head)->prev->flag)
		return ;
	while ((*head)->prev)
	{
		if ((*head)->prev->flag == 0)
			break ;
		(*head) = (*head)->prev;
	}
}

void	free_parenthese(t_rock *rock)
{
	t_rock	*tmp;

	while (rock)
	{
		tmp = rock;
		rock = rock->next;
		if (tmp->type == O_PARENTHIS || tmp->type == C_PARENTHIS)
		{
			free_2dd(tmp->cmd);
			free(tmp->arr);
			free(tmp);
		}
	}
}

t_tree	*ast_tokenes(t_rock *rock, t_env *env)
{
	t_tree	*root;

	root = ast_and(rock, env);
	return (root);
}
