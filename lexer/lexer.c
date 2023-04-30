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
		if ((*token) && ((*token)->type == PIPE || (*token)->type \
			== DPIPE || (*token)->type == D_AND))
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
	t_token	*tmp4;

	tmp = (*token);
	if (tmp->next)
	{
		if (tmp->next->type == CMD)
		{
			tmp2 = tmp->next;
			while (tmp && !(tmp->type == PIPE || \
				tmp->type == DPIPE || tmp->type == D_AND))
			{
				tmp3 = tmp;
				tmp = tmp->prev;
				if (!tmp || tmp->type == CMD)
				{
					if (!tmp)
					{
						tmp3->prev = tmp2;
						(*token)->next = tmp2->next;
						if (tmp2->next)
							tmp2->next->prev = (*token);
						tmp2->next = tmp3;
						tmp2->prev = tmp;
					}
					return ;
				}
			}
		}
	}
}

void	case_cmd_after_file(t_token *token)
{
	get_head(&token);
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

void	get_tail(t_token **head)
{
	if (!(*head))
		return ;
	if (!(*head)->next)
		return ;
	while ((*head)->next)
	{
		if ((*head)->next->flag == 0)
			break ;
		(*head) = (*head)->next;
	}
}

void	swap_token_char(t_token **a, t_token **b)
{
	char	*tmp;

	if (!(*b) || !(*a))
		return ;
	if ((*a)->next)
	{
		if ((*a)->next->type == C_PARENTHIS)
			return ;
	}
	tmp = (*a)->cmd[0];
	(*a)->cmd[0] = (*b)->cmd[0];
	(*b)->cmd[0] = tmp;
}

void	handle_followed_red(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp2;

	get_head(&token);
	while (token)
	{
		if (token->type == FILE)
		{
			tmp = token;
			token = token->next;
			if (!token)
				return ;
			while (token->next && (token->next->type == FILE || is_red(token->next->type)))
				token = token->next;
			if (token && token->type == FILE)
				swap_token_char(&tmp, &token);
		}
		if (!token)
			return ;
		token = token->next;
	}
}

void	lex_tokens(t_lexer *lex, char **env)
{
	t_token	*tmp;

	tmp = lex->tokens;
	while (tmp)
	{
		get_type(tmp);
		tmp = tmp->next;
	}
	join_cmd_and_arg(lex);
	put_operators_in_cmd(lex->tokens);
	case_of_arg_after_file(lex->tokens);
	case_cmd_after_file(lex->tokens);
	handle_followed_red(lex->tokens); // handle ls >out>out2>ou3 || wc <<EOF <<EOF2 <<EOF3
	// get_head(&lex->tokens);
	// while (lex->tokens)
	// {
	// 	printf("%s\n", lex->tokens->cmd[0]);
	// 	lex->tokens = lex->tokens->next;
	// }
	
	// if (lex->tokens->prev)
	// {
	// 	printf("%s\n", lex->tokens->prev->cmd[0]);
	// }
	// while (lex->tokens->next)
	// 	lex->tokens = lex->tokens->next;
	// while (lex->tokens)
	// {
	// 	printf("%s\n", lex->tokens->cmd[0]);
	// 	lex->tokens = lex->tokens->prev;
	// }
}
