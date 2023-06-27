/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:44:45 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/27 00:33:27 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_op(int a)
{
	if (a == PIPE || a == DPIPE \
		|| a == D_AND)
		return (1);
	return (0);
}

int	func5(t_token *token)
{
	while (token)
	{
		if (is_red(token->type) && token->next && (token->next->type == \
			O_PARENTHIS || token->next->type == C_PARENTHIS))
			return (ft_printf("syntax error near unexpected token `('\n"), 0);
		if (is_red(token->type) && token->next && token->next->type == PIPE)
			return (ft_printf("syntax error near unexpected token `|'\n"), 0);
		if (token->type == O_PARENTHIS && token->next \
			&& (is_op(token->next->type) || token->next->type == C_PARENTHIS))
			return (ft_printf("syntax error near unexpected token `('\n"), 0);
		if (token->type == -10 && token->next && token->next->type \
			== O_PARENTHIS)
			return (ft_printf("syntax error near unexpected token \n"), 0);
		if (token->type == C_PARENTHIS && token->next && token->next->type \
			== O_PARENTHIS)
			return (ft_printf("syntax error near unexpected token `('\n"), 0);
		if (token->type == C_PARENTHIS && token->next && token->next->type \
			== -10)
			return (ft_printf("minishell: syntax error near unexpected token"), \
				ft_printf(" `%s'\n", token->next->data), 0);
		if (is_red(token->type) && token->next && is_red(token->next->type))
			return (ft_printf("syntax error near unexpected token `<'\n"), 0);
		token = token->next;
	}
	return (1);
}
