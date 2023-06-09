/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:13:56 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/09 14:38:25 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_env(t_env **our_env)
{
	t_env	*tmp;

	while ((*our_env))
	{
		tmp = (*our_env);
		(*our_env) = (*our_env)->next;
		free(tmp->value);
		free(tmp->key);
		free(tmp);
		tmp = NULL;
	}
}

void	free_rock(t_rock **rock)
{
	t_rock	*tmp;

	while ((*rock))
	{
		tmp = (*rock);
		(*rock) = (*rock)->next;
		free_2dd(tmp->cmd);
		free(tmp->arr);
		free(tmp);
		tmp = NULL;
	}
}

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	if (tree->token)
	{
		free_2dd(tree->token->cmd);
		free(tree->token->arr);
		free(tree->token);
	}
	if (tree->heredoc)
	{
		free_tree(tree->heredoc->left);
		free_tree(tree->heredoc->right);
		free(tree->heredoc->name);
		free_2dd(tree->heredoc->token->cmd);
		free(tree->heredoc->token->arr);
		free(tree->heredoc->token);
		free(tree->heredoc);
	}
	free(tree);
	tree = NULL;
}

void	free_tokens(t_token **token)
{
	t_token	*tmp;

	while ((*token))
	{
		tmp = (*token);
		(*token) = (*token)->next;
		free(tmp->data);
		free(tmp);
		tmp = NULL;
	}
}
