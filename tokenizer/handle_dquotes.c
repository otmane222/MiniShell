/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:34:45 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/30 12:18:21 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'\
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	stor_data(t_token **t, char *line, t_var *var, char *stop)
{
	while (line[var->i] && !ft_strchr(stop, line[var->i]))
	{
		(*t)->data[var->counter] = line[var->i];
		var->counter = var->counter + 1;
		(*t)->data[var->counter] = '\0';
		var->i++;
	}
	if (!line[var->i])
		printf("Error!\n");
}

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void	handle_dquotes(char *line, t_var *var, t_token **token, int *i)
{
	var->i++;
	stor_data(token, line, var, "\"");
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
