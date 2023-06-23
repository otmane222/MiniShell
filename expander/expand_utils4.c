/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:08:44 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/23 12:08:46 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static char	*helpful_call(char *line, int *start, t_env *our_env)
{
	char	*s;
	char	*str;

	if (line[*start] == '?')
		return (questio_mark(line, start));
	s = get_env_var(&line[(*start)]);
	str = ft_getenv(s, our_env);
	if (str)
	{
		line = ft_strreplace_no_q(str, line, s, (*start));
		(*start) = (*start) + ft_strlen(str) - 1;
	}
	else
	{
		line = ft_strreplace_non(line, s, (*start));
		(*start) = (*start) - 1;
	}
	free(str);
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
	free(str);
	while (line[(*start)] && line[(*start)] != '$' \
		&& line[(*start)] != '\"')
		(*start)++;
	return (line);
}

static char	*expand_var_nq(char *line, int *start, t_env *our_env)
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
			line = helpful_call(line, start, our_env);
		if (!line[(*start)] || line[(*start)] == '\'' || line[(*start)] == '\"')
			break ;
		(*start)++;
	}
	if (line[(*start)] == '\'' || line[(*start)] == '\"')
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

char	*continue_expand(char *line, t_env *our_env)
{
	int	i;

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
			skip_in_q(line, &i, '\'');
		if (line[i] == '\"')
			line = expand_var_dq(line, &i, our_env);
		if (line[i] == '$')
			line = expand_var_nq(line, &i, our_env);
		if (line[0] == '\0')
			return (free(line), NULL);
		if (!line[i] && i != -1)
			break ;
		i++;
	}
	return (line);
}
