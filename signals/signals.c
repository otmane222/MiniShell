/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 06:08:02 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/25 16:40:30 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_there_here_doc(int k)
{
	static int	i = 0;

	if (k == -1)
		return (i);
	else
		i = k;
	return (i);
}

int	std_in_fd(int k)
{
	static int	i = 0;

	if (k == -1)
		return (i);
	else
		i = k;
	return (i);
}

void	handle_signals(int signal)
{
	int	fd;

	if (signal == SIGINT)
	{
		if (is_there_here_doc(-1))
		{
			printf("\n");
			fd = dup(STDIN_FILENO);
			close(STDIN_FILENO);
			std_in_fd(fd);
			stop_execution(-2);
		}
		else if (!runnig_cmd(-1))
		{
			printf("\n");
			rl_on_new_line();
			// rl_replace_line("", 0);
			rl_redisplay();
		}
		g_exit_status = 1;
	}
	if (signal == SIGQUIT)
		return ;
}

void	signal_handler_call(void)
{
	// rl_catch_signals = 0;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	signal(SIGTSTP, SIG_IGN);
}
