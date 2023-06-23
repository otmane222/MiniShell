/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:41:41 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/22 18:43:02 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*get_value(char *line)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (i == 0)
		return (NULL);
	i++;
	j = i;
	while (line[i])
		i++;
	value = malloc(i - j + 1);
	if (!value)
		return (NULL);
	i = 0;
	while (line[j])
		value[i++] = line[j++];
	value[i] = '\0';
	return (value);
}

char	*get_key(char *line)
{
	int		i;
	char	*key;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '=')
		i++;
	if (line[i] == ' ')
		return (printf("Error : syntax error !\n"), NULL);
	key = malloc(i + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '=')
	{
		key[i] = line[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

t_env	*put_env_to_new(char **env)
{
	t_env		*our_env;

	if (!env || !*env)
		return (NULL);
	our_env = ft_lstnew_env(get_value(*env), get_key(*env));
	env++;
	while (*env)
	{
		ft_lstadd_back_env(&our_env, ft_lstnew_env(get_value(*env), \
				get_key(*env)));
		env++;
	}
	ft_init();
	remove_from_env(ft_strdup("OLDPWD"), &our_env);
	return (our_env);
}
