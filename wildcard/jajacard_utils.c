/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jajacard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:56:35 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/01 18:33:09 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char	*ft_strreplace_no_q(char *str, char *token, int len, int index)
{
	int		i;
	int		j;
	char	*ret;

	ret = malloc (sizeof(char) * (ft_strlen(str) + \
			(ft_strlen(token) + 4)));
	i = 0;
	j = 0;
	while (token[i] && i < index)
		ret[j++] = token[i++];
	ret[j++] = '\'';
	i = -1;
	while (str[++i])
		ret[j++] = str[i];
	ret[j++] = '\'';
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

/*
	files->counter = found_it(&files->name[files->counter], to_find[i], \
		ft_strlen(&files->name[files->counter]));
	if (!files->counter)
		files->usable = 0;
	if (i == 0 && var->check && !ft_strncmp(files->name, \
	to_find[i], ft_strlen(to_find[i]) + 1))
		files->usable = 0;
	if (!to_find[i + 1] && var->end && \
	!ft_strnstr(&files->name[ft_strlen(files->name) \
		- ft_strlen(to_find[i])], \
		to_find[i], ft_strlen(&files->name[counter])))
		files->usable = 0;
*/