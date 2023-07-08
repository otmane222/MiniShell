/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:37:48 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/05 13:25:09 by oaboulgh         ###   ########.fr       */
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

void	get_std_in(void)
{
	if (!isatty(STDIN_FILENO) && std_in_fd(-1) != -2)
	{
		dup2(std_in_fd(-1), STDIN_FILENO);
		close(std_in_fd(-1));
		std_in_fd(-2);
	}
}
