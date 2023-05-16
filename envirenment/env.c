/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:23:35 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/16 17:45:50 by nakebli          ###   ########.fr       */
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

// t_envinfo	*init_env_info(void)
// {
// 	t_envinfo	*envinfo;

// 	envinfo = malloc(sizeof(t_envinfo));
// 	if (!envinfo)
// 		return (NULL);
// 	envinfo->our_env = NULL;
// 	envinfo->copy_env = NULL;
// 	return (envinfo);
// }

static int	env_len(char **env)
{
	int	i;

	i = 0;
	while (*env)
	{
		env++;
		i++;
	}
	return (i);
}

char	**full_env_copy(char **env)
{
	char	**tmp;
	char	**env_copy;
	int		i;

	i = env_len(env);
	env_copy = malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (*env)
	{
		printf("%s\n", *env);
		env_copy[i] = ft_strdup(*env);
		env++;
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
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
