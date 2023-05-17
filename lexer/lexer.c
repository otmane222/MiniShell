/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:31:13 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/04 18:28:38 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	put_type_of_tokens(t_token *tmp)
{
	while (tmp)
	{
		get_type(tmp);
		tmp = tmp->next;
	}
}

void	put_type_of_rocks(t_rock *tmp)
{
	while (tmp)
	{
		get_type1(tmp);
		tmp = tmp->next;
	}
}

t_rock	*init_rock(void)
{
	t_rock	*rock;

	rock = malloc(sizeof(t_rock));
	if (!rock)
		return (NULL);
	rock->cmd = NULL;
	rock->next = NULL;
	rock->prev = NULL;
	rock->flag = 1;
	rock->type = -10;
	return (rock);
}

void	join_cmd(t_rock *rock, t_token *token, t_var *var, int g)
{
	char	*str;

	str = ft_strdup(token->data);
	if (!rock->cmd)
		rock->cmd = malloc(sizeof(char *) * g);
	rock->cmd[var->i] = str;
	var->i++;
	rock->cmd[var->i] = NULL;
	var->j = 1;
}

void	init_var_to_0(t_var *var)
{
	var->i = 0;
	var->j = 0;
}

int	is_red2(int a)
{
	if (a == D_RED_OUT || a == RED_IN || a == RED_OUT || a == D_RED_IN)
		return (1);
	return (0);
}

int	is_stoper(int a)
{
	if (a == PIPE || a == DPIPE || a == D_AND || a == O_PARENTHIS || \
		a == C_PARENTHIS)
		return (1);
	return (0);
}

int	num_of_arg(t_token *token)
{
	int	i;

	i = 2;
	while (token && !is_stoper(token->type))
	{
		token = token->next;
		if (token && (!is_red2(token->type) || token->type != FILE || \
			token->type != LIMITER))
			i++;
	}
	return (i);
}

void	new_rock(t_rock **rock)
{
	t_rock	*tmp;

	(*rock)->next = init_rock();
	tmp = (*rock);
	(*rock) = (*rock)->next;
	(*rock)->prev = tmp;
}

void	put_the_op_in_cmd(t_rock *rock, t_token *token)
{
	char	*str;

	str = ft_strdup(token->data);
	if (!rock->cmd)
		rock->cmd = malloc(sizeof(char *) * ft_strlen(token->data));
	rock->cmd[0] = str;
	rock->cmd[1] = NULL;
}

void	join_c(t_rock *rock, t_token **token, t_var *var)
{
	t_token	*tmp;

	while ((*token) && (*token)->type == -10)
	{
		join_cmd(rock, *token, var, num_of_arg(*token));
		(*token) = (*token)->next;
	}
}

void	 join_arg_with_cmd(t_rock *rock, t_token *token)
{
	t_token	*tmp2;
	t_var	var;

	init_var_to_0(&var);
	while (token)
	{
		if (token->type == -10)
		{
			join_c(rock, &token, &var);
			if (!token)
				return ;
			new_rock(&rock);
		}
		if (token->type != -10)
		{
			init_var_to_0(&var);
			put_the_op_in_cmd(rock, token);
			if (token->next)
				new_rock(&rock);
		}
		token = token->next;
	}
}

void	get_head1(t_rock **head)
{
	if (!(*head))
		return ;
	if (!(*head)->prev)
		return ;
	while ((*head)->prev)
		(*head) = (*head)->prev;
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->data);
		free(tmp);
	}
}

t_rock	*lex_token(t_token *token)
{
	t_rock	*rock;

	put_type_of_tokens(token);
	rock = init_rock();
	join_arg_with_cmd(rock, token);
	free_tokens(token);
	put_type_of_rocks(rock);
	case_cmd_after_file(rock);
	get_head1(&rock);
	case_of_arg_after_file(rock);
	return (rock);
}
