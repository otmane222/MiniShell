/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:02:54 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/23 12:02:56 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_env(t_rock **rock, t_env **env, int outfile)
{
	t_env	*tmp;

	tmp = *env;
	if (!(*rock) || (*rock)->cmd[1])
	{
		g_exit_status = 1;
		return ;
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->key, outfile);
		ft_putchar_fd('=', outfile);
		ft_putstr_fd(tmp->value, outfile);
		ft_putchar_fd('\n', outfile);
		tmp = tmp->next;
	}
	g_exit_status = 0;
}
