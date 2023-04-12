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
