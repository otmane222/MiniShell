/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 06:50:27 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/30 11:46:32 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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
}
