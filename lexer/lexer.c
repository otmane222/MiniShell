/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:04:23 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/12 15:08:46 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	put_operators_in_cmd(t_token *token)
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

void	del_token2(t_token *tok)
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!tok)
		return ;
	tmp = tok->next;
	tmp2 = tok->prev;
	free(tok);
	tok = NULL;
	if (tmp)
		tmp->prev = tmp2;
	if (tmp2)
		tmp2->next = tmp;
}

void	get_cmd(t_token **token)
{
	t_token	*tmp;
	t_var	var;

	if (!(*token)->next)
		return ;
	if ((*token)->next->type != CMD)
		return ;
	tmp = (*token)->next;
	while ((*token) && (*token)->type != CMD)
	{
		*token = (*token)->prev;
		if ((*token)->type == PIPE || (*token)->type == DPIPE || (*token)->type == D_AND)
		{
			(*token) = tmp;
			return ;
		}
	}
	if (!(*token))
		return ;
	var.i = 0;
	var.j = 0;
	while ((*token)->cmd[var.i])
		var.i++;
	while ((*token)->cmd[var.j])
	{
		(*token)->cmd[var.i] = tmp->cmd[var.j];
		var.i++;
		var.j++;
		(*token)->cmd[var.i] = NULL;
	}
	del_token2(tmp);
}

void	case_of_arg_after_file(t_token *token)
{
	while (token)
	{
		if (token->type == FILE)
		{
			get_cmd(&token);
			if (!token)
				break ;
		}
		token = token->next;
	}
	
}

void	fix(t_token **token)
{
	t_token	*tmp;
	t_token	*tmp2;
	t_token	*tmp3;

	if ((*token)->next)
	{
		if ((*token)->next->type == CMD)
		{
			tmp2 = (*token)->next;
			tmp = (*token);
			while ((*token) && !((*token)->type == PIPE || (*token)->type == DPIPE || (*token)->type == D_AND))
			{
				(*token) = (*token)->prev;
				if ((*token)->type == CMD || !(*token))
				{
					(*token) = tmp2;
					return ;
				}
			}
			printf("got here\n");
			tmp3 = (*token)->next;
			tmp3->prev = tmp2;
			(*token)->next = tmp2;
			tmp->next = tmp2->next;
			tmp2->prev = (*token);
			if (tmp2->next)
				tmp2->next->prev = tmp;
			tmp2->next = tmp3;
		}
	}
}

void	case_cmd_after_file(t_token *token)
{
	while (token)
	{
		if (token->type == FILE)
		{
			fix(&token);
			if (!token)
				break ;
		}
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
	join_cmd_and_arg(lex);
	put_operators_in_cmd(lex->tokens);
	case_of_arg_after_file(lex->tokens);
	case_cmd_after_file(lex->tokens);
	while (tmp)
	{
		int i = 0;
		printf("-----%d--\n", tmp->type);
		while (tmp->cmd[i])
		{
			printf("token[%s]\n", tmp->cmd[i]);
			i++;
		}
		tmp = tmp->next;
	}
}
