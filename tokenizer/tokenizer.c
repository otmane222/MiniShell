/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:28:07 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/11 14:03:08 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	char_type(char c)
{
	if (c == '|')
		return (D_PIPE);
	else if (c == '\'')
		return (D_SQOUTE);
	else if (c == '\"')
		return (D_DQOUTE);
	else if (c == '>')
		return (D_BIGGER);
	else if (c == '<')
		return (D_SMALLER);
	else if (c == ' ')
		return (D_SPACE);
	else if (c == '(')
		return (D_OPAR);
	else if (c == ')')
		return (D_CPAR);
	else if (c == '&')
		return (D_AND);
	else
		return (D_GEN);
}

void	del_node(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = token->next;
	tmp2 = token->prev;
	free(token->data);
	free(token);
	token = NULL;
	tmp->prev = tmp2;
	tmp2->next = tmp;
}

void	next_node(t_token **t, char *line, int *i)
{
	t_token	*temp;

	temp = init_token(ft_strlen(line));
	(*t)->next = temp;
	temp->prev = (*t);
	*t = temp;
	*i = 0;
}

int	first_step(t_token **token, char *line, t_var *var)
{
	if (char_type(line[var->i]) == D_GEN)
		handle_chars(line, var, token, &var->counter);
	else if (char_type(line[var->i]) == D_DQOUTE)
		handle_dquotes(line, var, token, &var->counter);
	else if (char_type(line[var->i]) == D_SQOUTE)
		handle_squotes(line, var, token, &var->counter);
	else if (char_type(line[var->i]) == D_SPACE)
		handle_spaces(line, var, token, &var->counter);
	else if (is_operator(line[var->i]))
		handle_seperators(line, var, token, &var->counter);
	else if (is_parenthese(line[var->i]))
		handle_parenthese(line, var, token, &var->counter);
	return (1);
}

int	get_token(t_token **token, char *line)
{
	t_var	*var;
	t_token	*tmp;

	init_var(&var);
	tmp = *token;
	while (line[++var->i])
	{
		var->check = first_step(token, line, var);
		if (!*token)
			return (free(var), get_head_token(token), 0);
		if (!line[var->i])
			break ;
	}
	get_head_token(token);
	if (!check_errors(*token))
		return (free(var), free_tokens(token), 0);
	free(var);
	wild_card_handle(&tmp);
	*token = tmp;
	return (1);
}
