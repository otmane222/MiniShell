/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 06:50:27 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/08 16:08:34 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	init_var(t_var **var)
{
	*var = malloc(sizeof(t_var));
	if (!var)
		return ;
	(*var)->i = -1;
	(*var)->j = 0;
	(*var)->check = 1;
	(*var)->status = 0;
	(*var)->counter = 0;
	(*var)->qoutes_flag = 0;
	(*var)->start = 0;
	(*var)->end = 0;
	(*var)->flag = 0;
}

void	handle_spaces(char *line, t_var *var, t_token **token, int *i)
{
	while (is_white_space(line[var->i]))
		var->i++;
	if (is_qoutes(line[var->i]))
	{
		if (line[var->i] == '\'')
			handle_squotes(line, var, token, i);
		else
			handle_dquotes(line, var, token, i);
	}
	else if (is_char(line[var->i]))
		handle_chars(line, var, token, i);
	else if (is_operator(line[var->i]))
		handle_seperators(line, var, token, i);
	else if (is_parenthese(line[var->i]))
		handle_parenthese(line, var, token, i);
}
