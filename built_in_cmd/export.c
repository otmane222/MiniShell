/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:54:04 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/26 17:28:30 by oaboulgh         ###   ########.fr       */
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

static void	print_export(char *key, char *value, int outfile)
{
	ft_putstr_fd("declare -x ", outfile);
	ft_putstr_fd(key, outfile);
	ft_putstr_fd("=\"", outfile);
	ft_putstr_fd(value, outfile);
	ft_putstr_fd("\"\n", outfile);
}

void	change_var(char **temp, int *i, t_env **env)
{
	while (*temp)
	{
		while ((*temp) && check_arguments(get_key(*temp), *temp, 2))
		{
			*i = 1;
			temp++;
		}
		if (!(*temp))
			break ;
		add_to_env(get_key(*temp), get_value(*temp), env);
		temp++;
	}
}

int	ft_export(t_rock **rock, t_env **env, int outfile)
{
	int		i;
	char	**temp;
	t_env	*temp_e;

	i = 0;
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
		change_var(temp, &i, env);
	if (i == 1)
		return (g_exit_status = 1, 0);
	return (g_exit_status = 0, 0);
}
