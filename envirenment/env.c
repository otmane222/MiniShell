/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:23:35 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/10 17:29:15 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*init_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->next = NULL;
	env->prev = NULL;
	env->value = NULL;
	env->key = NULL;
	return (env);
}

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
	(new)->next = 0;
	return (new);
}

void	ft_lstdelone_env(t_env **lst)
{
	t_env	*tmp;

	if (!lst || !(*lst))
		return ;
	tmp = (*lst);
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (!tmp->prev && tmp->next)
		(*lst) = (*lst)->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
	lst = NULL;
}

char	*get_key(char *line)
{
	int		i;
	char	*key;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	key = malloc(i + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '=')
	{
		key[i] = line[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_value(char *line)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '=')
		i++;
	i++;
	j = i;
	while (line[i])
		i++;
	value = malloc(i - j + 1);
	if (!value)
		return (NULL);
	i = j;
	j = 0;
	while (line[i])
	{
		value[j] = line[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

void	add_value(t_env *env, char *line)
{
	env->key = get_key(line);
	env->value = get_value(line);
}

t_env	*put_env_to_new(char **env)
{
	t_env	*our_env;
	t_env	*head;
	t_env	*tmp;
	t_env	*tmp2;

	our_env = init_env();
	head = our_env;
	while (*env)
	{
		if (!our_env)
			our_env = init_env();
		add_value(our_env, *env);
		our_env->next = init_env();
		tmp = our_env;
		our_env = our_env->next;
		our_env->prev = tmp;
		env++;
	}
	return (head);
}
