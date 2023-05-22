/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:33:28 by nakebli           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/17 14:16:45 by nakebli          ###   ########.fr       */
=======
/*   Updated: 2023/05/16 18:37:28 by nakebli          ###   ########.fr       */
>>>>>>> 5b403648007d759a46feb40e78a8dc3ec22f6161
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	builtin_cmds(t_rock **rock, t_env **env)
{
	if (ft_strncmp((*rock)->cmd[0], "export", 7) == 0)
		ft_export(rock, env);
	if (ft_strncmp((*rock)->cmd[0], "unset", 6) == 0)
		ft_unset(rock, env);
<<<<<<< HEAD
	if (ft_strncmp((*rock)->cmd[0], "env", 4) == 0)
		ft_env(rock, env);
=======
>>>>>>> 5b403648007d759a46feb40e78a8dc3ec22f6161
}
