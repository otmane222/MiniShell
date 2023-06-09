/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:54:04 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/09 18:26:49 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	**change_env(t_env *env)
{
	char	**str;
	char	*s1;
	int		i;
	t_env	*tmp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	str = malloc (sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		s1 = ft_strjoin("=", tmp->value);
		str[i++] = ft_strjoin(tmp->key, s1);
		free (s1);
		tmp = tmp->next;
	}
	return (str[i] = NULL, str);
}

void	add_to_env(char *var, char *val, t_env **env)
{
	t_env	*tmp;

	if (!var || !val)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, var, ft_strlen(var)) == 0 && \
			ft_strlen(tmp->key) == ft_strlen(var))
		{
			free(tmp->value);
			tmp->value = val;
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back_env(env, ft_lstnew_env(val, var));
}

void	ft_export(t_rock **rock, t_env **env, int outfile)
{
	char	**temp;
	t_env	*temp_e;

	temp = &(*rock)->cmd[1];
	if (!(*temp))
	{
		temp_e = *env;
		while (temp_e)
		{
			ft_putstr_fd("declare -x ", outfile);
			ft_putstr_fd(temp_e->key, outfile);
			ft_putstr_fd("=\"", outfile);
			ft_putstr_fd(temp_e->value, outfile);
			ft_putstr_fd("\"\n", outfile);
			temp_e = temp_e->next;
		}
	}
	else
	{
		while (*temp)
		{
			add_to_env(get_key(*temp), get_value(*temp), env);
			temp++;
		}
	}
}
