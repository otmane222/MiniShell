/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:06:39 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/23 12:06:39 by nakebli          ###   ########.fr       */
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

int	is_not_end(char *line, t_var *var)
{
	int	k;

	k = var->i;
	while (line[var->i] && is_white_space(line[var->i]))
		var->i++;
	if (!line[var->i])
		return (0);
	else
		var->i = k;
	return (1);
}

void	handle_chars(char *line, t_var *var, t_token **token, int *i)
{
	store_data(line, var, token, i);
	if (is_operator(line[var->i]))
	{
		next_node(token, line, i);
		handle_seperators(line, var, token, i);
	}
	else if (is_white_space(line[var->i]) && is_not_end(line, var))
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
