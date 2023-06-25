/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:03:37 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/25 08:24:00 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
	if (!key)
		return (0);
	if (key[0] != '_' && !ft_isalpha(key[0]))
		return (print_error2(j, key), free(key), 1);
	while (key[++i])
	{
		if ((!ft_isalnum(key[i]) && key[i] != '_'))
		{
			if (key[i] == '+' && key[i + 1] == '\0')
				return (free(key), 0);
			return (print_error2(j, key), free(key), 1);
		}
	}
	return (free(key), 0);
}

void	remove_from_env(char *var, t_env **env)
{
	t_env	*tmp;

	if (!var)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, var, ft_strlen(var)) == 0 && \
			ft_strlen(tmp->key) == ft_strlen(var))
		{
			ft_lstdelone_env1(&tmp, env);
			free (var);
			return ;
		}
		tmp = tmp->next;
	}
	free (var);
}

int	ft_unset(t_rock **rock, t_env **env)
{
	char	**temp;

	temp = &(*rock)->cmd[1];
	if (!temp)
		return (1);
	while (*temp)
	{
		if (check_arguments(get_key(*temp), 1))
			return (g_exit_status = 1, 1);
		remove_from_env(get_key(*temp), env);
		temp++;
	}
	return (g_exit_status = 0, 0);
}
