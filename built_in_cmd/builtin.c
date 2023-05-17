/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:33:28 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/17 14:16:45 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	builtin_cmds(t_rock **rock, t_env **env)
{
	if (ft_strncmp((*rock)->cmd[0], "export", 7) == 0)
		ft_export(rock, env);
	if (ft_strncmp((*rock)->cmd[0], "unset", 6) == 0)
		ft_unset(rock, env);
	if (ft_strncmp((*rock)->cmd[0], "env", 4) == 0)
		ft_env(rock, env);
}
