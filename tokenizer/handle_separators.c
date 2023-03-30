/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_seperators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:28:40 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/30 11:43:33 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	handle_seperators(char *line, t_var *var, t_token **token, int *i)
{
	while (line[var->i] && is_operator(line[var->i]))
	{
		(*token)->data[*i] = line[var->i];
		*i = *i + 1;
		(*token)->data[*i] = '\0';
		var->i++;
	}
	if (!line[var->i])
	{
		printf("Syntax Error!\n");
		return ;
	}
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
}
