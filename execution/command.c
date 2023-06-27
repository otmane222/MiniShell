/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:30:46 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/26 15:23:47 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	wait_last_cmd(t_data data)
{
	int	sig;

	waitpid(data.i, &data.status, 0);
	if (WIFEXITED(data.status))
		g_exit_status = WEXITSTATUS(data.status);
	else if (WIFSIGNALED(data.status))
	{
		sig = WTERMSIG(data.status);
		g_exit_status = sig + 128;
	}
	if (data.status)
		return (runnig_cmd(0), 1);
	return (runnig_cmd(0), 0);
}

void	free_cmd(char **str, int j)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (i < j)
	{
		free (str[i]);
		i++;
	}
	free (str);
}

char	**save_cmd(char **cmd, int j)
{
	char	**save;
	int		k;
	int		i;

	save = malloc(sizeof(char *) * (j + 1));
	if (!save)
		return (NULL);
	k = 0;
	i = 0;
	while (i < j)
	{
		if (cmd[i])
			save[k++] = ft_strdup(cmd[i]);
		i++;
	}
	save[k] = NULL;
	free_cmd(cmd, j);
	return (save);
}

char	**expander_in_execution(t_rock *rock, t_env **env)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (rock->cmd[j])
		j++;
	while (rock->cmd[i])
	{
		if (rock->arr[i] != -9)
			rock->cmd[i] = expand_line(rock->cmd[i], *env);
		i++;
	}
	i = 0;
	while (i < j)
	{
		if (rock->arr[i] != -9)
			rock->cmd[i] = deleted_q(rock->cmd[i]);
		i++;
	}
	return (save_cmd(rock->cmd, j));
}

int	handle_command(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	runnig_cmd(1);
	if (stop_execution(-1) == -2)
		return (runnig_cmd(0), stop_execution(0), 1);
	root->token->cmd = expander_in_execution(root->token, env);
	if (!root->token->cmd[0])
		return (0);
	if (built_in(root->token->cmd[0], root->token->cmd, env))
		return (runnig_cmd(0), run_built_in(root, data, env));
	data.i = fork();
	if (data.i < 0)
		return (perror("fork"), 1);
	if (data.i == 0)
		child_execute(root, data, env, list);
	if (root->token->is_last)
		return (wait_last_cmd(data));
	return (0);
}
