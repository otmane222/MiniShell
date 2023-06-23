/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_q.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:12:03 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/23 12:12:06 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*store_dq(char *str, char *line, int *i, int *j)
{
	*i = *i + 1;
	while (line[*i] && line[*i] != '\"')
	{
		str[*j] = line[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
	str[*j] = '\0';
	*i = *i + 1;
	if (line[*i] == '\"')
		str = store_dq(str, line, i, j);
	if (line[*i] == '\'')
		str = store_sq(str, line, i, j);
	return (str);
}

char	*store_sq(char *str, char *line, int *i, int *j)
{
	*i = *i + 1;
	while (line[*i] && line[*i] != '\'')
	{
		str[*j] = line[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
	str[*j] = '\0';
	*i = *i + 1;
	if (line[*i] == '\"')
		str = store_dq(str, line, i, j);
	if (line[*i] == '\'')
		str = store_sq(str, line, i, j);
	return (str);
}

char	*deleted_q(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!line)
		return (NULL);
	str = malloc(ft_strlen(line) + 1);
	if (!str)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'')
			str = store_sq(str, line, &i, &j);
		if (line[i] == '\"')
			str = store_dq(str, line, &i, &j);
		if (!line[i])
			break ;
		str[j] = line[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (free(line), str);
}
