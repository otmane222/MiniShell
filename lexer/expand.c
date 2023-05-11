/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:19:53 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/11 12:29:46 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*ft_strreplace_no_q(char *str, char *token, char *s, int index)
{
	int		i;
	int		j;
	char	*ret;

	ret = malloc (sizeof(char) * (ft_strlen(str) + \
			(ft_strlen(token) - (ft_strlen(s)) + 3)));
	i = 0;
	j = 0;
	while (token[i] && i < index - 1)
		ret[j++] = token[i++];
	ret[j++] = '\'';
	i = -1;
	while (str[++i])
		ret[j++] = str[i];
	ret[j++] = '\'';
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

static char	*ft_strreplace(char *str, char *token, char *s, int index)
{
	int		i;
	int		j;
	char	*ret;

	ret = malloc (sizeof(char) * (ft_strlen(str) + \
			(ft_strlen(token) - (ft_strlen(s)) + 1)));
	i = 0;
	j = 0;
	while (token[i] && i < index - 1)
		ret[j++] = token[i++];
	i = -1;
	while (str[++i])
		ret[j++] = str[i];
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

static char	*ft_strreplace_non(char *token, char *s, int index)
{
	int		i;
	int		j;
	char	*ret;

	ret = malloc (sizeof(char) * ((ft_strlen(token) - (ft_strlen(s)) + 1)));
	i = 0;
	j = 0;
	while (token[i] && i < index - 1)
		ret[j++] = token[i++];
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

// verified √
static char	*get_env_var(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?'))
		i++;
	str = malloc (sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?'))
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_getenv(char *var, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->key, var, ft_strlen(env->key)) == 0 \
			&& ft_strlen(env->key) == ft_strlen(var))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char *expand_var_nq(char *line, int *start, t_env *our_env)
{
	int		j;
	char	*str;
	char	*s;
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
		{
			s = get_env_var(&line[(*start)]);
			str = ft_getenv(s, our_env);
			if (str)
			{
				line = ft_strreplace_no_q(str, line, s, (*start));
				(*start) = (*start) + ft_strlen(str) - 1;
				flag = 1;
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
		}
		if (!line[(*start)] || line[(*start)] == '\'' || line[(*start)] == '\"')
			break ;
		(*start)++;
	}
	if ((line[(*start)] == '\'' && !flag) || line[(*start)] == '\"')
		(*start) = (*start) - 1;
	return (line);
}

char	*expand_var_dq(char *line, int *start, t_env *our_env)
{
	int		j;
	char	*str;
	char	*s;

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
		{
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
		}
		if (!line[(*start)] || line[*start] == '\"')
			break ;
		(*start)++;
	}
	return (line);
}

char *expand_line(char *line, t_env *our_env)
{
	int		i;
	int		flag;
	int		j;

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
		{
			line = expand_var_dq(line, &i, our_env);
		}
		if (line[i] == '$')
			line = expand_var_nq(line, &i, our_env);
		if (!line[i] && i != -1)
			break ;
		i++;
	}
	return (line);
}
