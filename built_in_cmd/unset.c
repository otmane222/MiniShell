/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:55:04 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/16 18:40:48 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_lstdelone_env1(t_env **env, t_env **head)
{
	t_env	*tmp1;
	t_env	*tmp2;
	t_env	*tmp3;

	if (!env || !(*env))
		return ;
	tmp3 = *env;
	tmp1 = (*env)->prev;
	tmp2 = (*env)->next;
	if (tmp1)
		tmp1->next = tmp2;
	if (tmp2)
		tmp2->prev = tmp1;
	if (!tmp1 && tmp2)
		*head = tmp2;
	if (!tmp2 && tmp1)
		*head = tmp1;
	free(tmp3->key);
	tmp3->key = NULL;
	free(tmp3->value);
	tmp3->value = NULL;
	free(tmp3);
	tmp3 = NULL;
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
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_unset(t_rock **rock, t_env **env)
{
	char	**temp;
	t_env	*temp_e;

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
