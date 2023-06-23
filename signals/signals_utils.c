/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:11:37 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/23 12:11:40 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	runnig_cmd(int k)
{
	static int	i = 0;

	if (k == -1)
		return (i);
	else
		i = k;
	return (i);
}

int	stop_execution(int k)
{
	static int	i = 0;

	if (k == -1)
		return (i);
	else
		i = k;
	return (i);
}
