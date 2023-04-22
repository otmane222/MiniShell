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

#include "tree.h"

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

// t_tree	*ast_parenthese(t_tree **root, t_token *toke)
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

int	is_red(int a)
{
	if (a == D_RED_OUT || a == RED_IN || a == RED_OUT || a == D_RED_IN)
		return (1);
	return (0);
}

t_tree	*case_file(t_token *tmp, t_tree *tree)
{
	if (tmp->next)
	{
		if (tmp->next->flag && tmp->type == FILE)
		{
			tree->left = init_tree();
			tree->left->token = tmp;
			tree->token = tmp->next;
			return (tree);
		}
	}
	tree->token = tmp;
	return (tree);
}

t_tree	*ast_and_or(t_token *tok)
{
	t_token	*tmp;
	t_tree	*tree;
	t_var	var;

	get_head(&tok);
	tmp = tok;
	tree = init_tree();
	var.i = 0;
	while (tok && tok->flag)
	{
		if (tok->type == D_AND || tok->type == DPIPE)
		{
			var.i = 1;
			break ;
		}
		tok = tok->next;
	}
	if (var.i == 0)
		return (case_file(tmp, tree));
	else if (var.i = 1)
	{
		tok->flag = 0;
		tree->token = tok;
		tree->left = ast_and_or(tok->prev);
		tree->right = ast_and_or(tok->next);
		return (tree);
	}
}

t_tree	*ast_pipe(t_token *tok)
{
	t_var	var;
	t_token	*tmp;
	t_tree	*tree;

	tree = init_tree();
	get_head(&tok);
	tmp = tok;
	var.i = 0;
	while (tok && tok->flag)
	{
		if (tok->type == PIPE)
		{
			var.i = 1;
			break ;
		}
		tok = tok->next;
	}
	if (var.i == 0)
	{
		tok = tmp;
		return (ast_and_or(tok));
	}
	else if (var.i)
	{
		tok->flag = 0;
		tree->token = tok;
		tree->left = ast_pipe(tok->prev);
		tree->right = ast_pipe(tok->next);
		return (tree);
	}
}

t_tree	*ast_redirections(t_token *tok)
{
	t_var	var;
	t_token	*tmp;
	t_tree	*tree;

	tree = init_tree();
	get_head(&tok);
	if (!tok)
		return (NULL);
	tmp = tok;
	var.i = 0;
	while (tok && tok->flag)
	{
		if (is_red(tok->type))
		{
			var.i = 1;
			break ;
		}
		tok = tok->next;
	}
	if (var.i == 0)
	{
		tok = tmp;
		return (ast_pipe(tok));
	}
	else if (var.i)
	{
		tok->flag = 0;
		tree->token = tok;
		tree->left = ast_redirections(tok->prev);
		tree->right = ast_redirections(tok->next);
		return (tree);
	}
}

static void	free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

void	del_token(t_token *tok)
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!tok)
		return ;
	tmp = tok->next;
	tmp2 = tok->prev;
	free_2d(tok->cmd);
	free(tok);
	tok = NULL;
	if (tmp)
		tmp->prev = tmp2;
	if (tmp2)
		tmp2->next = tmp;
}

t_tree	*case_no_next(t_token *begin, t_token *tok, t_token *b, t_tree *tree)
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

t_tree	*case_no_perv(t_token *begin, t_token *tok, t_token *b, t_tree *tree)
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

t_tree	*case_nothing(t_token *begin, t_token *tok, t_token *b, t_tree *tree)
{
	t_token	*tmp;

	tmp = begin->next;
	del_token(begin);
	del_token(tok);
	return (ast_parenthese(tmp));
}

int	ck_pr(int a, int b)
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
}

t_tree	*case_both_exit(t_token *begin, t_token *tok, t_token *b, t_tree *tree)
{
	int	a;
	int	g;

	a = begin->prev->type;
	g = tok->next->type;
	if (begin->prev->flag == 0)
		return (case_no_perv(begin, tok, b, tree));
	else if (tok->next->flag == 0)
		return (case_no_next(begin, tok, b, tree));
	else if (ck_pr(a, g) == 0 || ck_pr(a, g) == 2 || ck_pr(a , g) == 4)
		return (case_no_next(begin, tok, b, tree));
	else if (ck_pr(a, g) == 1 || ck_pr(a, g) == 3 || ck_pr(a , g) == 5)
		return (case_no_perv(begin, tok, b, tree));


}

t_tree	*cases(t_token *begin, t_token *tok, t_token *b, t_tree *tree)
{
	if (!begin->prev && !tok->next)
		return (case_nothing(begin, tok, b, tree));
	else if (begin->prev && !tok->next)
		return (case_no_next(begin, tok, b, tree));
	else if (!begin->prev && tok->next)
		return (case_no_perv(begin, tok, b, tree));
	else if (begin->prev && tok->next)
		return (case_both_exit(begin, tok, b, tree));
}

t_tree	*ast_parenthese(t_token *tok)
{
	t_var	var;
	t_token	*begin;
	t_token	*b;
	t_tree	*tree;

	tree = init_tree();
	var.i = -1;
	begin = NULL;
	get_head(&tok);
	b = tok;
	while (tok && tok->flag)
	{
		if (tok->type == O_PARENTHIS)
		{
			if (!begin)
				begin = tok;
			if (var.i == -1)
				var.i++;
			var.i++;
		}
		else if (tok->type == C_PARENTHIS)
		{
			var.i--;
			if (var.i == 0)
				break ;
		}
		tok = tok->next;
	}
	if (var.i == -1)
	{
		tok = b;
		return (ast_redirections(tok));
	}
	else if (var.i == 0)
		return (cases(begin, tok, b, tree));
}

t_tree	*ast_tokenes(t_lexer *lex)
{
	t_tree	*root;
	t_tree	*tmp;
	t_var	*var;

	init_var_2(&var);
	root = ast_parenthese(lex->tokens);

	return (root);
}
