/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:56:35 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/21 04:29:31 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char	*ft_strreplace1(char *str, char *token, int len, int index)
{
	int		i;
	int		j;
	char	*ret;

	ret = malloc (sizeof(char) * (ft_strlen(str) + \
			(ft_strlen(token) + 1)));
	i = 0;
	j = 0;
	while (token[i] && i < index)
		ret[j++] = token[i++];
	i = -1;
	while (str[++i])
		ret[j++] = str[i];
	i = index + len;
	while (token[i])
	{
		ret[j++] = token[i++];
		ret[j] = '\0';
	}
	ret[j] = '\0';
	free(token);
	return (ret);
}

int	found_it(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	if (little[i] == '\0')
		return (0);
	while (len && big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[i + j] == little[j] && i + j < len)
			{
				if (!little[j + 1])
					return (i + j + 1);
				j++;
			}
		}
		i++;
	}
	return (0);
}

void	skip_chars(char *line, int *j, int *i)
{
	*i = *i + 1;
	while (line[*j] && line[*j] != '*' && !is_valid(line[*j]))
	{
		if (line[*j] == '\'')
			skip_q(line, j, '\'');
		if (line[*j] == '\"')
			skip_q(line, j, '\"');
		if (line[*j] == '*')
			break ;
		*j = *j + 1;
	}
}

int	is_not_q(char *line, int *j)
{
	if (line[*j] && line[*j + 1] && line[*j] == '\'' && line[*j + 1] == '\'')
	{
		*j = *j + 2;
		return (0);
	}
	else if (line[*j] && line[*j + 1] && line[*j] == '\"' && \
		line[*j + 1] == '\"')
	{
		*j = *j + 2;
		return (0);
	}
	return (1);
}

int	num_of_char(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[j] && !is_valid(line[j]))
	{
		if (line[j] == '*')
			skip_najmat(line, &j);
		while (!is_not_q(line, &j))
			;
		if (line[j] && line[j] != '*')
			skip_chars(line, &j, &i);
		if (!line[j])
			return (i);
	}
	return (i);
}
