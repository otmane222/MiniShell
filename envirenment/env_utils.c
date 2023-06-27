/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:47:33 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/25 21:18:47 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*ft_lstlast_env(t_env *lst)
{
	while (lst)
	{
		if (!(lst)->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (lst)
	{
		if (!(*lst))
			(*lst) = new;
		else
		{
			temp = ft_lstlast_env(*lst);
			temp->next = new;
			new->prev = temp;
		}
	}
}

t_env	*ft_lstnew_env(char *value, char *key)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	(new)->value = value;
	(new)->key = key;
	(new)->next = NULL;
	(new)->prev = NULL;
	return (new);
}

void	ft_lstdelone_env1(t_env **env, t_env **head)
{
	t_env	*tmp;
	t_env	*prev;
	t_env	*next;

	tmp = *env;
	prev = tmp->prev;
	next = tmp->next;
	if (!env || !(*env))
		return ;
	if (prev)
		prev->next = next;
	else
		*head = next;
	if (next)
		next->prev = prev;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
	*env = NULL;
}
