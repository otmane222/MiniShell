/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:16:13 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/12 14:19:16 by oaboulgh         ###   ########.fr       */
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

void	join_cmd(t_token *tmp, t_token *token, t_var *var, int *g)
{
	if (!tmp->cmd)
	{
		tmp->cmd = malloc(sizeof(char *) * (*g));
		*g = (*g) - 1;
	}
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

void	init_var_to_0(t_var *var)
{
	var->i = 0;
	var->j = 0;
}

void	join_cmd_and_arg(t_lexer *lex)
{
	t_token	*tmp;
	t_token	*token;
	t_var	var;

	init_var_to_0(&var);
	token = lex->tokens;
	while (token && token->type != -10)
		token = token->next;
	tmp = token;
	while (token)
	{
		if (token->type == -10)
			join_cmd(tmp, token, &var, &lex->n_token);
		else
		{
			if (var.j)
				small_call(tmp, token);
			tmp = token->next;
			init_var_to_0(&var);
		}
		token = token->next;
	}
	if (tmp)
		tmp->next = NULL;
}
