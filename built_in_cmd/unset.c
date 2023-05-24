/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:55:04 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/23 22:07:14 by oaboulgh         ###   ########.fr       */
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
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_unset(t_rock **rock, t_env **env)
{
	char	**temp;

	temp = &(*rock)->cmd[1];
	if (!temp)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	while (*temp)
	{
		remove_from_env(get_key(*temp), env);
		temp++;
	}
}
