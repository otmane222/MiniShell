/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_squotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:12:23 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/12 15:07:49 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_qoutes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

static void	stor_data(t_token **t, char *line, t_var *var, char *stop)
{
	while (line[var->i] && !ft_strchr(stop, line[var->i]))
	{
		(*t)->data[var->counter] = line[var->i];
		var->counter = var->counter + 1;
		(*t)->data[var->counter] = '\0';
		var->i++;
	}
	(*t)->data[var->counter] = '\0';
	if (!line[var->i])
	{
		free_tokens(t);
		printf("syntax error\n");
		return ;
	}
	(*t)->flag = 0;
}

static void	check_after(t_token **token, char *line, t_var *var, int *i)
{
	if (is_white_space(line[var->i]) || is_operator(line[var->i]))
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
	else if (is_parenthese(line[var->i]))
	{
		next_node(token, line, i);
		handle_parenthese(line, var, token, i);
	}
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
		else
			check_after(token, line, var, i);
	}
}
