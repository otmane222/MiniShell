/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:28:07 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/30 12:18:04 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*init_token(size_t x)
{
	t_token	*token;

	token = malloc (sizeof(t_token));
	if (!token)
		exit (1);
	token->data = malloc(x + 1);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

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
	else
		return (D_GEN);
}

void	next_node(t_token **t, char *line, int *i)
{
	t_token	*temp;

	temp = init_token(ft_strlen(line) + 1);
	(*t)->next = temp;
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
	return (1);
}

void	get_token(t_lexer *lex, char *line)
{
	t_var	*var;
	t_token	*token;

	init_var(&var);
	token = init_token(ft_strlen(line) + 1);
	token->data = malloc(ft_strlen(line) + 1);
	lex->tokens = token;
	while (line[++var->i])
	{
		var->check = first_step(&token, line, var);
		if (!line[var->i])
			break ;
	}
	while (lex->tokens)
	{
		printf("token[%s]---\n", lex->tokens->data);
		lex->tokens = lex->tokens->next;
	}
}
