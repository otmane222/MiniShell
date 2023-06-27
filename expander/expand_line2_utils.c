/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line2_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:17:28 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/26 16:50:43 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	num_op(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_operator(str[i]))
			j += 2;
		i++;
	}
	return (j);
}

char	*str_full(char *str, char *ret, int *flag, int *j)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_operator(str[i]))
		{
			ret[(*j)] = '\'';
			(*j) = (*j) + 1;
			*flag = 1;
		}
		ret[(*j)] = str[i];
		(*j) = (*j) + 1;
		if (*flag == 1)
		{
			ret[(*j)] = '\'';
			(*j) = (*j) + 1;
			*flag = 0;
		}
	}
	return (ret);
}

char	*ft_strreplace_no_q2(char *str, char *token, char *s, int index)
{
	int		i;
	int		j;
	int		flag;
	char	*ret;

	flag = 0;
	ret = malloc (sizeof(char) * (ft_strlen(str) + \
			(ft_strlen(token) - (ft_strlen(s)) + num_op(str) + 1)));
	i = 0;
	j = 0;
	while (token[i] && i < index - 1)
		ret[j++] = token[i++];
	ret = str_full(str, ret, &flag, &j);
	i = index + ft_strlen(s);
	while (token[i])
	{
		ret[j++] = token[i++];
		ret[j] = '\0';
	}
	ret[j] = '\0';
	free(token);
	return (ret);
}

char	*check_str(char *line, t_env *our_env, int *start)
{
	char	*str;
	char	*s;

	s = get_env_var(&line[(*start)]);
	str = ft_getenv(s, our_env);
	if (str)
	{
		line = ft_strreplace_no_q2(str, line, s, (*start));
		(*start) = (*start) + ft_strlen(str) - 1;
	}
	else if (!is_white_space(line[*start + ft_strlen(s)]) \
		&& line[*start + ft_strlen(s)] \
		&& !is_operator(line[*start + ft_strlen(s)]) \
			&& !is_qoutes(line[*start + ft_strlen(s)]))
	{
		line = ft_strreplace_non(line, s, (*start));
		(*start) = (*start) - 1;
	}
	else
		(*start) = (*start) + ft_strlen(str);
	free(s);
	free(str);
	return (line);
}

char	*helpful_call2(char *line, int *start, t_env *our_env)
{
	if (line[*start] == '?')
		return (questio_mark(line, start));
	line = check_str(line, our_env, start);
	while (line[(*start)] && line[(*start)] != '$' && \
	line[(*start)] != '\'' && line[(*start)] != '\"')
		(*start)++;
	return (line);
}
