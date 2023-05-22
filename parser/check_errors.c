/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:31:00 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/22 16:12:56 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	func(t_token *token)
{
	while (token)
	{
		if (token->next)
		{
			if (token->type == token->next->type && token->type != -10)
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
				printf("syntax error near unexpected token `('\n");
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

int	check_errors(t_token *token)
{
	put_type_of_tokens(token);
	if (!func(token) || !func2(token) || \
		!func3(token))
		return (0);
	return (1);
}
