/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:39:38 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/09 16:48:34 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	is_operator2(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == ')' \
		|| c == '(')
		return (1);
	return (0);
}

int	is_valid(int a)
{
	if (is_white_space(a) || is_operator2(a))
		return (1);
	return (0);
}

void	check_first_char(t_token *tok, t_var *var)
{
	if (is_valid(tok->data[var->i]))
	{
		var->j = var->i + 1;
		if (tok->data[var->j] == '*')
			var->check = 0;
		var->start = var->i + 1;
	}
}

int	short_cut(char *line, t_var *var, t_var *va)
{
	if (!line || line[var->start] == '\0' || is_valid(line[var->start]))
		return (0);
	if (line[var->start] == '*')
	{
		skip_najmat(line, &var->start);
		if (!line[var->start] || is_valid(line[var->start]))
		{
			var->i = var->start;
			return (0);
		}
	}
	va->i = var->start;
	while (line[va->i] && line[va->i] != '*')
	{
		if (line[va->i] == '\'')
			skip_q(line, &va->i, '\'');
		if (line[va->i] == '\"')
			skip_q(line, &va->i, '\"');
		if (!line[va->i])
			break ;
		va->i++;
	}
	va->j = 0;
	va->i = var->start;
	return (1);
}

char	*chars(char *line, t_var *var)
{
	char	*str;
	t_var	va;

	while (!is_not_q(line, &var->start))
		;
	if (!short_cut(line, var, &va))
		return (NULL);
	str = malloc(sizeof(char) * va.i - var->start + 1);
	if (!str)
		return (NULL);
	while (line[va.i] && line[va.i] != '*' && !is_valid(line[va.i]))
	{
		if (line[va.i] == '\'')
			str = store_datas(str, line, &va, var);
		if (line[va.i] == '\"')
			str = store_datad(str, line, &va, var);
		if (!line[va.i] || is_valid(line[var->start]) || line[va.i] == '*')
			break ;
		str[va.j++] = line[va.i++];
	}
	if (!line[va.i] || is_valid(line[var->start]))
		var->end = 1;
	str[va.j] = '\0';
	var->start += ft_strlen(str);
	return (str);
}
