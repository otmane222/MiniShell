/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:06:48 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/23 12:06:48 by nakebli          ###   ########.fr       */
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

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}

static void	stoor_data(t_token **t, char *line, t_var *var, char *stop)
{
	(*t)->data[var->counter] = line[var->i];
	var->counter = var->counter + 1;
	(*t)->data[var->counter] = '\0';
	var->i++;
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
		get_head_token(t);
		free_tokens(t);
		printf("syntax error\n");
		return ;
	}
	(*t)->data[var->counter] = line[var->i];
	var->counter = var->counter + 1;
	(*t)->data[var->counter] = '\0';
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

void	handle_dquotes(char *line, t_var *var, t_token **token, int *i)
{
	stoor_data(token, line, var, "\"");
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
