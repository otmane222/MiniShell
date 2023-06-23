/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:54:04 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/23 08:29:30 by oaboulgh         ###   ########.fr       */
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
		if (ft_strncmp(tmp->key, var, ft_strlen(var) + 1) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = val;
			return (free(var));
		}
		tmp = tmp->next;
	}
	ft_lstadd_back_env(env, ft_lstnew_env(val, var));
}

void	edit_env(char *var, char *val, t_env **env)
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
			if (tmp->value)
				free(tmp->value);
			tmp->value = val;
			return ;
		}
		tmp = tmp->next;
	}
}

static void	print_export(char *key, char *value, int outfile)
{
	ft_putstr_fd("declare -x ", outfile);
	ft_putstr_fd(key, outfile);
	ft_putstr_fd("=\"", outfile);
	ft_putstr_fd(value, outfile);
	ft_putstr_fd("\"\n", outfile);
}

int	ft_export(t_rock **rock, t_env **env, int outfile)
{
	char	**temp;
	t_env	*temp_e;

	temp = &(*rock)->cmd[1];
	if (!(*temp))
	{
		temp_e = *env;
		while (temp_e)
		{
			print_export(temp_e->key, temp_e->value, outfile);
			temp_e = temp_e->next;
		}
	}
	else
	{
		while (*temp)
		{
			if (check_arguments(get_key(*temp), 2))
				return (g_exit_status = 1, 1);
			add_to_env(get_key(*temp), get_value(*temp), env);
			temp++;
		}
	}
	return (g_exit_status = 0, 0);
}
