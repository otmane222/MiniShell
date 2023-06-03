/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:56:35 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/03 14:13:11 by oaboulgh         ###   ########.fr       */
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
	ret[j++] = ' ';
	i = index + len;
	while (token[i])
	{
		ret[j++] = token[i++];
		ret[j] = '\0';
	}
	ret[j] = '\0';
	// free(token);
	return (ret);
}

int	found_it(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;
	char	*pt;

	i = 0;
	pt = 0;
	if (little[i] == '\0')
		return (0);
	while (len && big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			pt = (char *)big + i;
			j = 0;
			while (big[i + j] == little[j] && i + j < len)
			{
				if (!little[j + 1])
					return (i + j + 1);
				j++;
			}
			pt = 0;
		}
		i++;
	}
	return (0);
}

void	skip_najmat(char *line, int *j)
{
	while (line[*j] && line[*j] == '*')
		*j = *j + 1;
}

void	skip_chars(char *line, int *j, int *i)
{
	*i = *i + 1;
	while (line[*j] && line[*j] != '*' && line[*j] != ' ')
		*j = *j + 1;
}

int	num_of_char(char *line)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (line[j] && line[j] != ' ')
	{
		if (line[j] == '*')
			skip_najmat(line, &j);
		if (line[j] && line[j] != '*')
			skip_chars(line, &j, &i);
		if (!line[j])
			return (i);
	}
	return (i);
}