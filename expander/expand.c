/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:19:53 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/30 14:32:34 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static char	*helpful_call(char *line, int *start, t_env *our_env, int *flag)
{
	char	*s;
	char	*str;

	str = NULL;
	if (line[*start] == '?')
	{
		str = ft_itoa(g_exit_status);
		line = ft_strreplace_no_q(str, line, "?", (*start));
		free(str);
		(*start) = (*start) + ft_strlen(str) - 1;
		return (line);
	}
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

static void	skip_spaces(char *line, int *start)
{
	while (line[*start] && is_white_space(line[*start]))
		*start = *start + 1;
}

void	skip_in_q(char *line, int *start, char *stop)
{
	*start = *start + 1;
	while (line[*start] && !ft_strchr(stop, line[*start]))
		*start = *start + 1;
	if (line[*start] == '\"')
		*start = *start + 1;
	if (line[*start] && !is_operator(line[*start]))
		skip_char(line, start);
}

void	skip_char(char *line, int *start)
{
	while (line[*start] && !is_white_space(line[*start]) \
		&& line[*start] != '\"' && line[*start] != '\'' && \
			!is_operator(line[*start]))
		*start = *start + 1;
	if (line[*start] && line[*start] == '\"')
		skip_in_q(line, start, "\"");
	if (line[*start] && line[*start] == '\'')
		skip_in_q(line, start, "\'");
}

static void	skip_until(char *line, int *start)
{
	*start = *start + 2;
	skip_spaces(line, start);
	skip_char(line, start);
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

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			skip_until(line, &i);
			if (!line[i])
				return (line);
		}
		if (line[i] == '\'')
			skip_in_q(line, &i, "\'");
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
