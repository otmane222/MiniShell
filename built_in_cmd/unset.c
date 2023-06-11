/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:55:04 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/11 01:25:14 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
			return (1);
		remove_from_env(get_key(*temp), env);
		temp++;
	}
	return (0);
}
