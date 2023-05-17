/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:19:53 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/17 17:43:47 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static char	*helpful_call(char *line, int *start, t_env *our_env, int *flag)
{
	char	*s;
	char	*str;

	s = get_env_var(&line[(*start)]);
	str = ft_getenv(s, our_env);
	if (str)
	{
		line = ft_strreplace_no_q(str, line, s, (*start));
		(*start) = (*start) + ft_strlen(str) - 1;
		*flag = 1;
	}
	else
	{
		line = ft_strreplace_non(line, s, (*start));
		(*start) = (*start) - 1;
	}
	free(s);
	while (line[(*start)] && line[(*start)] != '$' && \
		line[(*start)] != '\'' && line[(*start)] != '\"')
		(*start)++;
	return (line);
}

static char	*assister_fun(char *line, int *start, t_env *our_env)
{
	char	*s;
	char	*str;

	s = get_env_var(&line[(*start)]);
	str = ft_getenv(s, our_env);
	if (str)
	{
		line = ft_strreplace(str, line, s, (*start));
		(*start) = (*start) + ft_strlen(str) - 1;
	}
	else
	{
		line = ft_strreplace_non(line, s, (*start));
		(*start) = (*start) - 1;
	}
	free(s);
	while (line[(*start)] && line[(*start)] != '$' \
		&& line[(*start)] != '\"')
		(*start)++;
	return (line);
}

static char	*expand_var_nq(char *line, int *start, t_env *our_env)
{
	int		j;
	int		flag;

	flag = 0;
	j = 0;
	while (line[(*start)] && line[(*start)] != '\'' && line[(*start)] != '\"')
	{
		flag = 0;
		if (line[(*start)] && line[(*start)] == '$')
		{
			j++;
			if (j == 2)
				j = 0;
		}
		if (line[(*start)] && line[(*start)] != '$' && j == 1)
			line = helpful_call(line, start, our_env, &flag);
		if (!line[(*start)] || line[(*start)] == '\'' || line[(*start)] == '\"')
			break ;
		(*start)++;
	}
	if ((line[(*start)] == '\'' && !flag) || line[(*start)] == '\"')
		(*start) = (*start) - 1;
	return (line);
}

static char	*expand_var_dq(char *line, int *start, t_env *our_env)
{
	int		j;

	j = 0;
	(*start)++;
	while (line[(*start)] && line[(*start)] != '\"')
	{
		if (line[(*start)] && line[(*start)] == '$')
		{
			j++;
			if (j == 2)
				j = 0;
		}
		if (line[(*start)] && line[(*start)] != '$' && j == 1)
			line = assister_fun(line, start, our_env);
		if (!line[(*start)] || line[*start] == '\"')
			break ;
		(*start)++;
	}
	return (line);
}

char	*expand_line(char *line, t_env *our_env)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		if (line[i] == '\"')
			line = expand_var_dq(line, &i, our_env);
		if (line[i] == '$')
			line = expand_var_nq(line, &i, our_env);
		if (!line[i] && i != -1)
			break ;
		i++;
	}
	return (line);
}
