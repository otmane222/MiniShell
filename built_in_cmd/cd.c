/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:03:21 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/30 16:39:40 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_cd(char *path, t_env **env)
{
	add_to_env("OLDPWD", getcwd(NULL, 0), env);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	add_to_env("PWD", getcwd(NULL, 0), env);
	return (0);
}
