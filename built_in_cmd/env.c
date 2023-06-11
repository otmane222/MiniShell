/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:11:02 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/11 13:14:47 by oaboulgh         ###   ########.fr       */
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
