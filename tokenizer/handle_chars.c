/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 06:08:48 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/12 14:36:51 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_char(char c)
{
	if (!is_white_space(c) && !is_operator(c) && !is_qoutes(c) && \
	!is_parenthese(c))
		return (1);
	return (0);
}

static void	store_data(char *line, t_var *var, t_token **token, int *i)
{
	while (line[var->i] && !is_operator(line[var->i]) \
		&& !is_white_space(line[var->i]) && !is_qoutes(line[var->i]) \
			&& !is_parenthese(line[var->i]))
	{
		(*token)->data[*i] = line[var->i];
		*i = *i + 1;
		(*token)->data[*i] = '\0';
		var->i++;
	}
}

void	handle_chars(char *line, t_var *var, t_token **token, int *i)
{
	store_data(line, var, token, i);
	if (is_operator(line[var->i]))
	{
		next_node(token, line, i);
		handle_seperators(line, var, token, i);
	}
	else if (is_white_space(line[var->i]))
	{
		next_node(token, line, i);
		handle_spaces(line, var, token, i);
	}
	else if (is_qoutes(line[var->i]))
	{
		if (line[var->i] == '\'')
			handle_squotes(line, var, token, i);
		else
			handle_dquotes(line, var, token, i);
	}
	else if (is_parenthese(line[var->i]))
	{
		next_node(token, line, i);
		handle_parenthese(line, var, token, i);
	}
}
