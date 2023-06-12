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
	i = -1;
	while (str[++i])
	{
		if (is_operator(str[i]))
		{
			ret[j++] = '\'';
			flag = 1;
		}
		ret[j++] = str[i];
		if (flag == 1)
		{
			ret[j++] = '\'';
			flag = 0;
		}
	}
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

static char	*helpful_call(char *line, int *start, t_env *our_env)
{
	char	*s;
	char	*str;

	str = NULL;
	if (line[*start] == '?')
	{
		str = ft_itoa(g_exit_status);
		line = ft_strreplace_no_q2(str, line, "?", (*start));
		(*start) += ft_strlen(str) - 1;
		free(str);
		return (line);
	}
	s = get_env_var(&line[(*start)]);
	str = ft_getenv(s, our_env);
	if (str)
	{
		line = ft_strreplace_no_q2(str, line, s, (*start));
		(*start) = (*start) + ft_strlen(str) - 1;
	}
	else
		(*start) = (*start) + ft_strlen(str);
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
		(*start) = (*start) + ft_strlen(str) - 1;
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

static void	skip_spaces(char *line, int *start)
{
	while (line[*start] && is_white_space(line[*start]))
		*start = *start + 1;
}

static void	skip_until(char *line, int *start)
{
	if ((line[(*start)] == '<' && line[(*start) + 1] == '<')  || (line[(*start)] == '>' && line[(*start) + 1] == '>'))
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
		*start = *start + 2;
		skip_spaces(line, start);
		skip_char(line, start);
	}
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

char	*expand_line2(char *line, t_env *our_env)
{
	int		i;

	i = 0;
	while (line[i])
	{
		skip_until(line, &i);
		if (!line[i])
			return (line);
		if (line[i] == '\'')
			skip_in_q(line, &i, '\'');
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
