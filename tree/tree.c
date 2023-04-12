/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:52:08 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/12 16:11:55 by oaboulgh         ###   ########.fr       */
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

// int	search_find_and(t_tree *root, t_token *token)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	while (token)
// 	{
// 		if (token->type == DPIPE || token->type == D_AND)
// 		{
// 			creat_foro3(root, token);
// 			search_find_red(root, tmp);
// 			break ;
// 		}
// 		token = token->next;
// 	}
// 	if (!token)
// 		search_find_red(root, tmp);
// 	token = tmp;
// 	return (0);
// }

// int	search_find_red(t_tree *root, t_token *token)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	while (token)
// 	{
// 		if (token->type == RED_IN || token->type == RED_OUT || \
// 			token->type == D_RED_IN || token->type == D_RED_OUT)
// 		{
// 			creat_foro3(root, token);
// 			search_find_red(root, tmp);
// 		}
// 		token = token->next;
// 	}
// 	token = tmp;
// 	return (0);
// }

// void	creat_foro3(t_tree *root, t_token *t)
// {
// 	root->right = init_tree();
// 	root->left = init_tree();
// 	root->token = t;
// }

// void	split_with_and_or(t_token *token, t_tree *root)
// {
// 	t_tree	*tmp;

// 	if (!token)
// 		return ;
// 	if (search_find_and(root, token))
// 		printf("+\n");
// 	else
// 		split_with_and_or(token->next, root);
// }

// void	skip_parenthese(t_token *token, t_tree *root)
// {
// 	while (token->type == C_PARENTHIS)
// 		token = token->next;
// 	if (!token)
// 		root->token = token;
// }

// void	del_token(t_token *token)
// {
// 	t_token	*tmp;

// 	if (token->next)
// 	{
// 		tmp = token->next;
// 	}
// 	if (token)
// 	{
// 		free(token->data);
// 		free_2d(token->cmd);
// 		free(token);
// 		token = NULL;
// 	}
// }

// void	get_head(t_token **head)
// {
// 	if (!(*head) || !(*head)->prev)
// 		return ;
// 	while ((*head)->prev)
// 	{
// 		if ((*head)->prev->flag == 0)
// 		{
// 			(*head)->prev = NULL;
// 			break ;
// 		}
// 		(*head) = (*head)->prev;
// 	}
// }

// t_token	*ast_parenthese(t_tree **root, t_token **toke)
// {
// 	t_token	*begin;
// 	t_token	*first;
// 	t_var	var;

// 	var.j = 0;
// 	begin = (*toke);
// 	first = NULL;
// 	get_head(toke);
// 	if (!(*toke)->next && !(*toke)->prev)
// 		return ((*toke));
// 	while ((*toke))
// 	{
// 		if ((*toke)->type == O_PARENTHIS)
// 		{
// 			if (var.j == 0)
// 				first = (*toke);
// 			var.j++;
// 		}
// 		else if ((*toke)->type == C_PARENTHIS)
// 		{
// 			var.j--;
// 			if (var.j == 0)
// 			{
// 				(*toke)->flag = 0;
// 				break ;
// 			}
// 		}
// 		*toke = (*toke)->next;
// 	}
// 	if (!(*toke)->next && first && !first->prev)
// 	{
// 		begin = begin->next;
// 		del_token(begin->prev);
// 		(*toke) = (*toke)->prev;
// 		del_token((*toke)->next);
// 		(*toke) = begin;
// 		var.j = 0;
// 		ast_parenthese(root, toke);
// 	}
// 	else if ((*toke)->next && first)
// 	{
// 		begin = (*toke)->next;
// 		(*toke)->next->flag = 0;
// 		(*root)->right = ast_parenthese(root, &(*toke)->next->next);
// 		(*toke)->next = NULL;
// 		(*root)->left = ast_parenthese(root, &(*toke)->prev);
// 		return (begin);
// 	}
// 	else if (!(*toke)->next && first && first->prev)
// 	{
// 		begin = first->prev;
// 		(*root)->token = begin;
// 		if ((*toke)->prev)
// 		{
// 			(*toke)->prev->flag = 0;
// 			(*root)->left = ast_parenthese(root, &first->prev->prev);
// 		}
// 		return (begin);
// 	}
// }

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

void	get_head(t_token **head)
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

t_tree	*ast_parenthese(t_tree **root, t_token **tok)
{
	t_var	var;
	t_token	*begin;

	var.i = -1;
	begin = NULL;
	get_head(tok);
	while ((*tok))
	{
		if ((*tok)->type == O_PARENTHIS)
		{
			if (!begin)
				begin = (*tok)
			if (var.i == -1)
				var.i++;
			var.i++;
		}
		else if ((*tok)->type == C_PARENTHIS)
		{
			var.i--;
			if (var.i == 0)
				break ;
		}
		(*tok) = (*tok)->next;
	}
	if (var.i == -1)
		(*root) = ast_redirections(root, tok);
	else if (begin)
	{
		
	}
}

t_tree	*ast_tokenes(t_lexer *lex)
{
	t_tree	*root;
	t_var	*var;

	init_var_2(&var);
	root = init_tree();
	// root->token = ast_parenthese(&root, &lex->tokens);

	return (root);
}
