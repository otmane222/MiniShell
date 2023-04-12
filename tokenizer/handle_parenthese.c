/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parenthese.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:35:47 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/12 14:35:30 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_parenthese(char c)
{
	if (c == ')' || c == '(')
		return (1);
	return (0);
}

void	handle_parenthese(char *line, t_var *var, t_token **token, int *i)
{
	(*token)->data[*i] = line[var->i];
	*i = *i + 1;
	(*token)->data[*i] = '\0';
	var->i++;
	if (line[var->i])
		next_node(token, line, i);
	if (is_white_space(line[var->i]))
		handle_spaces(line, var, token, i);
	else if (is_char(line[var->i]))
		handle_chars(line, var, token, i);
	else if (is_qoutes(line[var->i]))
	{
		if (line[var->i] == '\'')
			handle_squotes(line, var, token, i);
		else
			handle_dquotes(line, var, token, i);
	}
	else if (is_operator(line[var->i]))
		handle_seperators(line, var, token, &var->counter);
	else if (is_parenthese(line[var->i]))
		handle_parenthese(line, var, token, &var->counter);
}
