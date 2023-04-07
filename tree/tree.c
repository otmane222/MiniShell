/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:52:08 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/06 14:28:46 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	search_find_and(t_tree *root, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (token)
	{
		if (token->type == DPIPE || token->type == D_AND)
		{
			creat_foro3(root, token);
			search_find_red(root, tmp);
			break ;
		}
		token = token->next;
	}
	if (!token)
		search_find_red(root, tmp);
	token = tmp;
	return (0);
}

int	search_find_red(t_tree *root, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (token)
	{
		if (token->type == REDIRECTOR_IN || token->type == REDIRECTOR_OUT || \
			token->type == D_REDIRECTOR_IN || token->type == D_REDIRECTOR_OUT)
		{
			creat_foro3(root, token);
			search_find_red(root, tmp);
		}
		token = token->next;
	}
	token = tmp;
	return (0);
}

void	creat_foro3(t_tree *root, t_token *t)
{
	root->right = init_tree();
	root->left = init_tree();
	root->token = t;
}

void	split_with_and_or(t_token *token, t_tree *root)
{
	t_tree	*tmp;

	if (!token)
		return ;
	if (search_find_and(root, token))
	else
		split_with_and_or(token->next, root);
}
