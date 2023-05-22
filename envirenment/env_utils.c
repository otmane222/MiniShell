/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:47:33 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/17 15:36:58 by nakebli          ###   ########.fr       */
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
