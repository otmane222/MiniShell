/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:33:20 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/22 02:45:11 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

t_rock	*get_last(t_rock *rock)
{
	if (!rock)
		return (NULL);
	if (!rock->next)
		return (rock);
	while (rock->next && rock->next->flag)
		rock = rock->next;
	return (rock);
}

int	check_red_exist(t_rock *rock, int *flag, int *i)
{
	if (rock->type == D_RED_IN)
	{
		if (rock->prev && rock->prev->type == C_PARENTHIS)
			*flag = 1;
		*i = 1;
		return (1);
	}
	return (0);
}

int	check_red_exist2(t_rock *rock, int *flag, int *i)
{
	if (rock->type == RED_OUT || rock->type \
		== D_RED_OUT || rock->type == RED_IN)
	{
		if (rock->prev && rock->prev->type == C_PARENTHIS)
			*flag = 1;
		*i = 1;
		return (1);
	}
	return (0);
}

char	*check_q(char *line, char *str, int *i, int *j)
{
	if (line[(*i)] == '$' && line[(*i) + 1] && line[(*i) + 1] == '\'')
		str = store_datass(str, line, i, j);
	if (line[(*i)] == '$' && line[(*i) + 1] && line[(*i) + 1] == '\"')
		str = store_datadd(str, line, i, j);
	return (str);
}

char	*handle_case(char *line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!str)
		return (NULL);
	while (line[i])
	{
		str = check_q(line, str, &i, &j);
		if (!line[i])
			break ;
		if ((line[i] == '$' && line[i + 1] && line[i + 1] == '\'') \
			|| (line[i] == '$' && line[i + 1] && line[i + 1] == '\"'))
			continue ;
		str[j] = line[i];
		j++;
		i++;
	}
	str[j] = '\0';
	free(line);
	return (str);
}
