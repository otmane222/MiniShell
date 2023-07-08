/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:11:02 by nakebli           #+#    #+#             */
/*   Updated: 2023/07/05 15:31:16 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	call_1(char *val, char *var, t_env *tmp)
{
	char	*new_val;

	if (var[ft_strlen(var) - 1] == '+')
	{
		var[ft_strlen(var) - 1] = '\0';
		if (tmp->value)
			new_val = ft_strjoin(tmp->value, val);
		else
			new_val = ft_strdup(val);
		if (tmp->value)
			free(tmp->value);
		tmp->value = new_val;
		free(val);
	}
	else
	{
		if (!val)
			return (free(var), free(val));
		if (tmp->value)
			free(tmp->value);
		tmp->value = val;
	}
	return (free(var));
}

void	add_to_env(char *var, char *val, t_env **env)
{
	t_env	*tmp;

	if (!var)
		return ;
	if (!(*env))
		return (ft_lstadd_back_env(env, ft_lstnew_env(val, var)));
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(var, tmp->key, ft_strlen(tmp->key)) == 0
			&& (ft_strlen(tmp->key) == ft_strlen (var)
				|| ft_strlen(tmp->key) + 1 == ft_strlen(var)))
			return (call_1(val, var, tmp));
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
	free(val);
}

void	ft_env(t_rock **rock, t_env **env, int outfile)
{
	t_env	*tmp;

	tmp = *env;
	if (!(*rock))
	{
		g_exit_status = 1;
		return ;
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->key, outfile);
		ft_putchar_fd('=', outfile);
		ft_putstr_fd(tmp->value, outfile);
		ft_putchar_fd('\n', outfile);
		tmp = tmp->next;
	}
	g_exit_status = 0;
}
