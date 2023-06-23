/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:21:19 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/22 03:02:42 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

t_tree	*call_ninja(t_tree *tree, t_rock *rock, t_env *env)
{
	tree->heredoc = malloc(sizeof(t_heredoc));
	if (!tree->heredoc)
		return (NULL);
	tree->heredoc->token = rock;
	tree->heredoc->left = NULL;
	tree->heredoc->right = NULL;
	write_in_here_doc(tree, env);
	is_there_here_doc(0);
	tree->heredoc->left = ast_red_her_doc(rock->prev, env);
	tree->heredoc->right = ast_red_her_doc(rock->next, env);
	return (tree);
}

static t_tree	*fill_right_left(t_tree *tree, t_rock *rock, \
			int flag, t_env *env)
{
	if (flag == 1)
		rock->red_p = 1;
	rock->flag = 0;
	if (rock->type == D_RED_IN)
		return (call_ninja(tree, rock, env));
	tree->token = rock;
	tree->left = ast_reds(rock->prev, env);
	tree->right = ast_reds(rock->next, env);
	return (tree);
}

static t_tree	*case_file(t_rock *tmp, t_tree *tree, t_env *env)
{
	t_rock	*tmp2;
	t_rock	*tmp3;

	tmp3 = get_last(tmp);
	if (tmp->type == O_PARENTHIS)
	{
		tmp2 = tmp->next;
		tmp2->is_exit = 1;
		del_token(tmp);
		del_token(tmp3);
		free(tree);
		return (ast_and(tmp2, env));
	}
	else
	{
		tree->token = tmp;
		tree->token->flag = 0;
		return (tree);
	}
}

t_tree	*ast_red_her_doc(t_rock *rock, t_env *env)
{
	t_var	var;
	t_rock	*tmp;
	t_tree	*tree;
	int		flag;

	if (!rock || !rock->flag)
		return (NULL);
	tree = init_tree();
	get_head(&rock);
	tmp = rock;
	var.i = 0;
	flag = 0;
	while (rock && rock->flag)
	{
		skip_parenthese(&rock);
		if (check_red_exist(rock, &flag, &var.i))
			break ;
		rock = rock->next;
	}
	if (var.i == 0)
		return (case_file(tmp, tree, env));
	else if (var.i)
		return (fill_right_left(tree, rock, flag, env));
	return (NULL);
}

t_tree	*ast_reds(t_rock *rock, t_env *env)
{
	t_var	var;
	t_rock	*tmp;
	t_tree	*tree;
	int		flag;

	if (!rock || !rock->flag)
		return (NULL);
	tree = init_tree();
	get_head(&rock);
	tmp = rock;
	get_tail(&rock);
	var.i = 0;
	flag = 0;
	while (rock && rock->flag)
	{
		skip_parenthese1(&rock);
		if (check_red_exist2(rock, &flag, &var.i))
			break ;
		rock = rock->prev;
	}
	if (var.i == 0)
		return (free(tree), ast_red_her_doc(tmp, env));
	else if (var.i)
		return (fill_right_left(tree, rock, flag, env));
	return (NULL);
}
