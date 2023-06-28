/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:33:20 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/28 18:42:32 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

int	check_red_exist2(t_rock *rock, int *flag, int *i)
{
	if (rock->type == RED_OUT || rock->type \
		== D_RED_OUT || rock->type == RED_IN || rock->type == D_RED_IN)
	{
		if (rock->prev && rock->prev->type == C_PARENTHIS)
			*flag = 1;
		*i = 1;
		return (1);
	}
	return (0);
}

char	*save_dollar(char *line, char *str, int *i, int *j)
{
	while (line[*i] && line[*i] == '$' && line[(*i) + 1] == '$')
	{
		str[*j] = line[*i];
		*i = *i + 1;
		*j = *j + 1;
		str[*j] = line[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
	if (line[*i] && line[*i] == '$')
		*i = *i + 1;
	return (str);
}

void	flag_line(char *line, int i, int *flag)
{
	if (line[i] == '\'' && flag == 0)
		(*flag) = 1;
	else if (line[i] == '\'' && (*flag) == 1)
		(*flag) = 0;
	else if (line[i] == '\"' && (*flag) == 0)
		(*flag) = 2;
	else if (line[i] == '\"' && (*flag) == 2)
		(*flag) = 0;
}

char	*store_a_char(char *line, char *str, int *i, int *j)
{
	str[(*j)] = line[(*i)];
	(*i) = (*i) + 1;
	(*j) = (*j) + 1;
	return (str);
}

char	*handle_case(char *line)
{
	char	*str;
	t_var	var;

	var.flag = 0;
	var.i = 0;
	var.j = 0;
	str = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!str)
		return (NULL);
	while (line[var.i])
	{
		flag_line(line, var.i, &var.flag);
		if ((var.flag == 2 || var.flag == 1))
		{
			str = store_a_char(line, str, &var.i, &var.j);
			continue ;
		}
		if (!var.flag && line[var.i] == '$' && line[var.i + 1] == '$')
			str = save_dollar (line, str, &var.i, &var.j);
		else if (!var.flag && line[var.i] == '$' && is_qoutes(line[var.i + 1]))
			var.i++;
		else
			str = store_a_char (line, str, &var.i, &var.j);
	}
	str[var.j] = '\0';
	free(line);
	ft_printf(":%s:\n", str);
	return (str);
}
