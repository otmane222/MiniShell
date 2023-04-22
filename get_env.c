/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:14:18 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/12 14:32:05 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get the PATH in env , it has every path to any command in bash

char	**get_env(char **env)
{
	int		i;
	char	*str;
	char	**rtn;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 5))
			break ;
		i++;
	}
	if (env[i])
	{
		str = env[i] + 5;
		rtn = ft_split(str, ':');
		return (rtn);
	}
	return (NULL);
}
