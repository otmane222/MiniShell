/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:26:41 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/08 18:42:23 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*ft_strreplace_no_q(char *str, char *token, char *s, int index)
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

char	*ft_strreplace(char *str, char *token, char *s, int index)
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

char	*ft_strreplace_non(char *token, char *s, int index)
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

char	*get_env_var(char *s)
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
