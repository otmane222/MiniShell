/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:04:23 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/07 18:21:48 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	get_type(t_token *t)
{
	if (strcmp("||", t->data) == 0)
		t->type = DPIPE;
	else if (strcmp("|", t->data) == 0)
		t->type = PIPE;
	else if (strcmp(">>", t->data) == 0)
		t->type = D_RED_OUT;
	else if (strcmp(">", t->data) == 0)
		t->type = RED_OUT;
	else if (strcmp("<<", t->data) == 0)
		t->type = D_RED_IN;
	else if (strcmp("<", t->data) == 0)
		t->type = RED_IN;
	else if (strcmp("&&", t->data) == 0)
		t->type = D_AND;
	else if (strcmp("(", t->data) == 0)
		t->type = O_PARENTHIS;
	else if (strcmp(")", t->data) == 0)
		t->type = C_PARENTHIS;
	else if (t->prev)
	{
		if (t->prev->type == RED_OUT || t->prev->type == RED_IN || \
			t->prev->type == D_RED_OUT)
			t->type = FILE;
	}
}

void	full_first_token(t_token **tmp, t_token **token)
{
	(*tmp) = (*token);
	(*tmp)->cmd = malloc(sizeof(char *) * 4);
	if (!(*tmp)->cmd)
		return ;
	(*tmp)->cmd[0] = (*token)->data;
	(*tmp)->cmd[1] = NULL;
}

void	join_cmd(t_token *tmp, t_token *token, t_var *var)
{
	if (!tmp->cmd)
		tmp->cmd = malloc(sizeof(char *) * 5);
	tmp->cmd[var->i] = token->data;
	var->i++;
	tmp->cmd[var->i] = NULL;
	var->j = 1;
}

void	small_call(t_token *tmp, t_token *token)
{
	tmp->next = token;
	token->prev = tmp;
}

void	join_cmd_and_arg(t_token *token)
{
	t_token	*tmp;
	t_var	var;

	var.i = 0;
	var.j = 0;
	while (token && token->type != -10)
		token = token->next;
	tmp = token;
	while (token)
	{
		if (token->type == -10)
			join_cmd(tmp, token, &var);
		else
		{
			if (var.j)
				small_call(tmp, token);
			tmp = token->next;
			var.i = 0;
			var.j = 0;
		}
		token = token->next;
	}
	if (tmp)
		tmp->next = NULL;
}

void	put_operators_in_cmd(t_token *token)
{
	while (token)
	{
		if (token->type != -10)
		{
			if (!token->cmd)
				token->cmd = malloc(sizeof(char *) * 5);
			token->cmd[0] = token->data;
			token->cmd[1] = NULL;
		}
		else if (token->type == -10)
			token->type = CMD;
		token = token->next;
	}
}

void	lex_tokens(t_lexer *lex, char **env)
{
	t_token	*tmp;

	tmp = lex->tokens;
	while (lex->tokens)
	{
		get_type(lex->tokens);
		lex->tokens = lex->tokens->next;
	}
	lex->tokens = tmp;
	join_cmd_and_arg(lex->tokens);
	lex->tokens = tmp;
	put_operators_in_cmd(lex->tokens);
}
