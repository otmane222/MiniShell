/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:54:04 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/11 01:26:16 by oaboulgh         ###   ########.fr       */
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
			if (tmp->value)
				free(tmp->value);
			tmp->value = val;
			return ;
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

void	print_error2(int i, char *str)
{
	if (i == 1)
		ft_printf("minishell: unset: ");
	else if (i == 2)
		ft_printf("minishell: export: ");
	ft_printf("`%s': not a valid identifier\n", str);
}

int	check_arguments(char *key, int j)
{
	int	i;

	i = 0;
	if (key[0] != '_' && !ft_isalpha(key[0]))
		return (print_error2(j, key), free(key), 1);
	while (key[++i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (print_error2(j, key), free(key), 1);
	}
	return (free(key), 0);
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
			if (check_arguments(get_key(*temp), 2))
				return (1);
			add_to_env(get_key(*temp), get_value(*temp), env);
			temp++;
		}
	}
	return (0);
}
