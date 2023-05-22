/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/05/17 14:41:41 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/22 14:34:51 by nakebli          ###   ########.fr       */
=======
/*   Created: 2023/05/10 15:23:35 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/16 17:45:50 by nakebli          ###   ########.fr       */
>>>>>>> 5b403648007d759a46feb40e78a8dc3ec22f6161
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

<<<<<<< HEAD
=======
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
	(new)->next = NULL;
	(new)->prev = NULL;
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
	while (line[i] && line[i] != ' ' && line[i] != '=')
		i++;
	if (line[i] == ' ')
		return (printf("Error : syntax error !\n"), NULL);
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

>>>>>>> 5b403648007d759a46feb40e78a8dc3ec22f6161
char	*get_value(char *line)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (i == 0)
		return (NULL);
	i++;
	j = i;
	while (line[i])
		i++;
	value = malloc(i - j + 1);
	if (!value)
		return (NULL);
	i = 0;
	while (line[j])
		value[i++] = line[j++];
	value[i] = '\0';
	return (value);
}

char	*get_key(char *line)
{
	int		i;
	char	*key;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '=')
		i++;
	if (line[i] == ' ')
		return (printf("Error : syntax error !\n"), NULL);
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

t_env	*put_env_to_new(char **env)
{
	t_env		*our_env;

	if (!env || !*env)
		return (NULL);
	our_env = ft_lstnew_env(get_value(*env), get_key(*env));
	env++;
	while (*env)
	{
		ft_lstadd_back_env(&our_env, ft_lstnew_env(get_value(*env), \
				get_key(*env)));
		env++;
	}
	return (our_env);
}
