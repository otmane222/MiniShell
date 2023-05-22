/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:31:00 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/22 22:45:58 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	func(t_token *token)
{
	if (token)
	{
		if (token->type == PIPE || token->type == DPIPE || token->type == D_AND)
		{
			printf("syntax error near unexpected token `|'\n");
			return (0);
		}
	}
	while (token)
	{
		if (token->next)
		{
			if (token->type == token->next->type && token->type != -10 \
				&& token->type != O_PARENTHIS && token->type != C_PARENTHIS)
			{
				printf("syntax error near unexpected token `%s'\n", \
					token->data);
				return (0);
			}
		}
		token = token->next;
	}
	return (1);
}

int	func2(t_token *token)
{
	while (token)
	{
		if ((token->type == FILE || token->type == LIMITER) \
			&& token->next)
		{
			if (token->next->type == O_PARENTHIS)
			{
				printf("syntax error near unexpected token2 `('\n");
				return (0);
			}
		}
		token = token->next;
	}
	return (1);
}

int	func3(t_token *token)
{
	int	i;

	while (token)
	{
		i = 0;
		while (token)
		{
			if (is_op(token->type))
				i++;
			else
				break ;
			token = token->next;
		}
		if (i > 2)
			return (printf("syntax error\n"), 0);
		if (!token)
			return (printf("syntax error\n"), 0);
		token = token->next;
	}
	return (1);
}

int	func4(t_token *token)
{
	int	i;

	i = -1;
	while (token)
	{
		if (token->type == O_PARENTHIS)
		{
			if (i == -1)
				i++;
			i++;
		}
		else if (token->type == C_PARENTHIS)
		{
			if (i == -1 || i == 0)
				return (printf("syntax error near unexpected token `)'\n"), 0);
			i--;
		}
		token = token->next;
	}
	if (i != 0 && i != -1)
		return (printf("syntax error unclosed parenthese\n"), 0);
	return (1);
}

int	func5(t_token *token)
{
	while (token)
	{
		if (is_red(token->type) && token->next && (token->next->type == \
			O_PARENTHIS || token->next->type == C_PARENTHIS))
			return (printf("syntax error near unexpected token `('\n"), 0);
		if (token->type == O_PARENTHIS && token->next \
			&& (is_op(token->next->type) || token->next->type == C_PARENTHIS))
			return (printf("syntax error near unexpected token `('\n"), 0);
		if (token->type == -10 && token->next && token->next->type \
			== O_PARENTHIS)
			return (printf("syntax error near unexpected token \n"), 0);
		if (token->type == C_PARENTHIS && token->next && token->next->type \
			== O_PARENTHIS)
			return (printf("syntax error near unexpected token `('\n"), 0);
		if (token->type == C_PARENTHIS && token->next && token->next->type \
			== -10)
			return (printf("syntax error near unexpected token `('\n"), 0);
		token = token->next;
	}
	return (1);
}

int	check_errors(t_token *token)
{
	put_type_of_tokens(token);
	if (!func(token) || !func2(token) || \
		!func3(token) || !func4(token) || !func5(token))
		return (0);
	return (1);
}
