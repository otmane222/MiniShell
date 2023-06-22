/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:30:15 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/22 01:32:40 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

int	is_red(int a)
{
	if (a == D_RED_OUT || a == RED_IN || a == RED_OUT || a == D_RED_IN)
		return (1);
	return (0);
}

void	get_tail(t_rock **head)
{
	if (!(*head) || !(*head)->flag)
		return ;
	if (!(*head)->next || !(*head)->next->flag)
		return ;
	while ((*head)->next)
	{
		if ((*head)->next->flag == 0)
			break ;
		(*head) = (*head)->next;
	}
}

void	skip_parenthese1(t_rock **rock)
{
	int	i;

	i = 0;
	if ((*rock)->type == C_PARENTHIS)
	{
		while ((*rock) && (*rock)->flag)
		{
			if ((*rock)->type == C_PARENTHIS)
				i++;
			else if ((*rock)->type == O_PARENTHIS)
			{
				i--;
				if (i == 0)
					break ;
			}
			*rock = (*rock)->prev;
		}
	}
}

char	*store_datass(char *str, char *line, int *i, int *j)
{
	*i = *i + 1;
	str[*j] = line[*i];
	*i = *i + 1;
	*j = *j + 1;
	while (line[*i] && line[*i] != '\'')
	{
		str[*j] = line[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
	str[*j] = line[*i];
	*i = *i + 1;
	*j = *j + 1;
	str[*j] = '\0';
	if (line[*i] == '\"')
		str = store_datadd(str, line, i, j);
	if (line[*i] == '\'')
		str = store_datass(str, line, i, j);
	return (str);
}

char	*store_datadd(char *str, char *line, int *i, int *j)
{
	*i = *i + 1;
	str[*j] = line[*i];
	*i = *i + 1;
	*j = *j + 1;
	while (line[*i] && line[*i] != '\"')
	{
		str[*j] = line[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
	str[*j] = line[*i];
	*i = *i + 1;
	*j = *j + 1;
	str[*j] = '\0';
	if (line[*i] == '\'')
		str = store_datass(str, line, i, j);
	if (line[*i] == '\"')
		str = store_datadd(str, line, i, j);
	return (str);
}
