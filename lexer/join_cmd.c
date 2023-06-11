/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:46:49 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/10 00:43:01 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_kind(int a)
{
	if (a == PIPE || a == DPIPE || a == D_AND || a == O_PARENTHIS || \
		a == C_PARENTHIS)
		return (1);
	if (a == D_RED_OUT || a == RED_IN || a == RED_OUT || a == D_RED_IN)
		return (2);
	return (0);
}

static int	num_of_arg(t_token *token)
{
	int	i;

	i = 2;
	while (token && is_kind(token->type) != 1)
	{
		token = token->next;
		if (token && (is_kind(token->type) != 2 || token->type != FILE || \
			token->type != LIMITER))
			i++;
	}
	return (i);
}

static void	put_the_op_in_cmd(t_rock *rock, t_token *token, t_var *var)
{
	char	*str;

	var->i = 0;
	var->j = 0;
	str = ft_strdup(token->data);
	if (!rock->cmd)
		rock->cmd = malloc(sizeof(char *) * 2);
	rock->type = token->type;
	rock->cmd[0] = str;
	rock->cmd[1] = NULL;
	rock->arr = malloc(sizeof(int));
	if (!rock->arr)
		return ;
	rock->arr[0] = token->flag;
}

static void	join_c(t_rock *rock, t_token **token, t_var *var)
{
	char	*str;
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = *token;
	while ((*token) && (*token)->type == -10)
	{
		i++;
		(*token) = (*token)->next;
	}
	if (!rock->arr)
		rock->arr = malloc(sizeof(int) * i + 1);
	if (!rock->arr)
		return ;
	*token = tmp;
	i = 0;
	while ((*token) && (*token)->type == -10)
	{
		str = ft_strdup((*token)->data);
		if (!rock->cmd)
			rock->cmd = malloc(sizeof(char *) * num_of_arg(*token));
		rock->cmd[var->i] = str;
		rock->arr[i] = (*token)->flag;
		var->i++;
		i++;
		var->j = 1;
		(*token) = (*token)->next;
	}
	rock->cmd[var->i] = NULL;
}

void	join_arg_with_cmd(t_rock *rock, t_token *token)
{
	t_var	var;

	var.i = 0;
	var.j = 0;
	while (token)
	{
		if (token->type == -10)
		{
			rock->expand = token->flag;
			join_c(rock, &token, &var);
			rock->type = CMD;
			if (!token)
				return ;
			new_rock(&rock);
		}
		if (token->type != -10)
		{
			rock->expand = token->flag;
			put_the_op_in_cmd(rock, token, &var);
			if (token->next)
				new_rock(&rock);
		}
		token = token->next;
	}
}
