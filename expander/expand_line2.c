/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:19:53 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/11 00:51:46 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

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
	else if (!is_white_space(line[*start + ft_strlen(s)]))
	{
		line = ft_strreplace_non(line, s, (*start));
		(*start) = (*start) - 1;
	}
	else
		(*start) = (*start) + ft_strlen(str) - 1;
	free(s);
	free(str);
	while (line[(*start)] && line[(*start)] != '$' \
		&& line[(*start)] != '\"')
		(*start)++;
	return (line);
}

static char	*expand_var_nq2(char *line, int *start, t_env *our_env)
{
	int		j;

	j = 0;
	while (line[(*start)])
	{
		if (line[(*start)] && line[(*start)] == '$')
		{
			j++;
			if (j == 2)
				j = 0;
		}
		if (line[(*start)] && line[(*start)] != '$' && j == 1)
			line = helpful_call2(line, start, our_env);
		if (!line[(*start)] || line[(*start)] == '\'' || line[(*start)] == '\"')
			break ;
		(*start)++;
	}
	if (line[(*start)] == '\'' || line[(*start)] == '\"')
		(*start) = (*start) - 1;
	return (line);
}

static void	skip_until2(char *line, int *start)
{
	if ((line[(*start)] == '<' && line[(*start) + 1] == '<') \
		|| (line[(*start)] == '>' && line[(*start) + 1] == '>'))
	{
		*start = *start + 2;
		skip_spaces(line, start);
		skip_char(line, start);
	}
	else if ((line[(*start)] == '<' && line[(*start) + 1] != '<'))
	{
		*start = *start + 1;
		skip_spaces(line, start);
		skip_char(line, start);
	}
	else if ((line[(*start)] == '>' && line[(*start) + 1] != '>'))
	{
		*start = *start + 1;
		skip_spaces(line, start);
		skip_char(line, start);
	}
}

static char	*expand_var_dq2(char *line, int *start, t_env *our_env)
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

char	*expand_line2(char *line, t_env *our_env)
{
	int		i;

	i = 0;
	while (line[i])
	{
		skip_until2(line, &i);
		if (!line[i])
			return (line);
		if (line[i] == '\'')
			skip_in_q(line, &i, '\'');
		if (line[i] == '\"')
			line = expand_var_dq2(line, &i, our_env);
		if (line[i] == '$')
			line = expand_var_nq2(line, &i, our_env);
		if (!line[i] && i != -1)
			break ;
		i++;
	}
	return (line);
}
