/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_squotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:12:23 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/30 12:28:01 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_qoutes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	handle_squotes(char *line, t_var *var, t_token **token, int *i)
{
	var->i++;
	stor_data(token, line, var, "\'");
	if (!line[var->i])
		return ;
	else
	{
		var->i++;
		if (!line[var->i])
			return ;
		else if (is_white_space(line[var->i]) || is_operator(line[var->i]))
		{
			next_node(token, line, i);
			if (is_operator(line[var->i]))
				handle_seperators(line, var, token, i);
			else
				handle_spaces(line, var, token, i);
		}
		else if (char_type(line[var->i]) == D_GEN)
			handle_chars(line, var, token, i);
		else if (char_type(line[var->i]) == D_DQOUTE)
			handle_dquotes(line, var, token, i);
		else if (char_type(line[var->i]) == D_SQOUTE)
			handle_squotes(line, var, token, i);
	}
}
