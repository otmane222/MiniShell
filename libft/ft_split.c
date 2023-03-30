/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:36:11 by nakebli           #+#    #+#             */
/*   Updated: 2022/10/29 16:23:57 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numofwords(const char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

static int	ft_wordlen(const char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static void	ft_free2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

static char	**fill2darr(const char *s, char c, int num, char **splitted)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < num)
	{
		while (*s == c)
			s++;
		len = ft_wordlen(s, c);
		splitted[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (splitted[i] == NULL)
		{
			ft_free2d(splitted);
			return (NULL);
		}
		j = 0;
		while (j < len)
			splitted[i][j++] = *s++;
		splitted[i][j] = '\0';
		i++;
	}
	splitted[i] = NULL;
	return (splitted);
}

char	**ft_split(char	const *s, char c)
{
	int		num;
	char	**splited;

	if (s == NULL)
		return (NULL);
	num = ft_numofwords(s, c);
	splited = (char **)malloc(sizeof(char *) * (num + 1));
	if (splited == NULL)
		return (NULL);
	splited = fill2darr(s, c, num, splited);
	return (splited);
}
