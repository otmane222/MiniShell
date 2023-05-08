/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:19:53 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/08 14:35:40 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_strreplace(char *str, char *token, char *s, int index)
{
	int		i;
	int		j;
	char	*ret;

	ret = malloc (sizeof(char) * (ft_strlen(str) + \
			(ft_strlen(token) - (ft_strlen(s)))));
	i = -1;
	while (token[++i] && token[i] != '$')
		ret[i] = token[i];
	j = -1;
	while (str[++j])
		ret[i++] = str[j];
	j = index + ft_strlen(s) + 1;
	while (token[j])
	{
		ret[i++] = token[j];
		j++;
	}
	ret[i] = '\0';
	free(token);
	return (ret);
}

char	*get_env_var(char *s)
{
	char	*str;
	int		i;

	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?'))
		i++;
	str = malloc (sizeof(char) * i);
	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?'))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	expand_1(t_token *token, int i)
{
	int		j;
	char	*str;
	char	*s;

	j = 0;
	while (token->data[i])
	{
		if (token->data[i] == '$')
		{
			j++;
			if (j == 2)
				j = 0;
		}
		if (token->data[i] != '$' && j == 1)
		{
			s = get_env_var(&token->data[i]);
			str = getenv(s);
			if (str)
				token->data = ft_strreplace(str, token->data, s, i - 1);
			else
			{
				free(token->data);
				token->data = ft_strdup("\0");
			}
			while (token->data[i] && token->data[i] != '$')
				i++;
		}
		if (!token->data[i])
			break ;
		i++;
	}
	return (1);
}

void	expand_tokens(t_token *token)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (token->data[i])
	{
		if (token->data[i] == '$')
		{
			j = expand_1(token, i);
			if (j)
				break ;
		}
		i++;
	}
}
