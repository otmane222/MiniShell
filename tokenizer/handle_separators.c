/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_separators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:28:40 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/12 15:04:25 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	store_data(char *line, t_var *var, t_token **token, int *i)
{
	int	k;

	k = var->i;
	while (line[var->i] && char_type(line[var->i]) == char_type(line[k]))
	{
		(*token)->data[*i] = line[var->i];
		*i = *i + 1;
		(*token)->data[*i] = '\0';
		var->i++;
	}
}

void	handle_seperators(char *line, t_var *var, t_token **token, int *i)
{
	store_data(line, var, token, i);
	if (!line[var->i])
		return ;
	next_node(token, line, i);
	if (is_operator(line[var->i]))
		handle_seperators(line, var, token, i);
	else if (is_white_space(line[var->i]))
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
	else if (is_parenthese(line[var->i]))
		handle_parenthese(line, var, token, i);
}

