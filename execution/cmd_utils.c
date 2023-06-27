/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 03:42:52 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/26 02:01:55 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	built_in(char *str, char **cmds, t_env **env)
{
	char	*arr;

	arr = last_arg(cmds);
	add_to_env(ft_strdup("_"), ft_strdup(arr), env);
	if (ft_strncmp(str, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "echo", 5) == 0)
		return (2);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (3);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (4);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (5);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (6);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (7);
	return (0);
}

int	run_built_in(t_tree *root, t_data data, t_env **env)
{
	if (ft_strncmp(root->token->cmd[0], "pwd", 4) == 0)
		return (ft_pwd(data.outfile_fd, env, NULL));
	else if (ft_strncmp(root->token->cmd[0], "echo", 5) == 0)
		ft_echo(data.outfile_fd, root->token->cmd);
	else if (ft_strncmp(root->token->cmd[0], "cd", 3) == 0)
		return (ft_cd(root->token->cmd[1], env, data.outfile_fd));
	else if (ft_strncmp(root->token->cmd[0], "exit", 5) == 0)
		ft_exit(root);
	else if (ft_strncmp(root->token->cmd[0], "unset", 6) == 0)
		return (ft_unset(&root->token, env));
	else if (ft_strncmp(root->token->cmd[0], "export", 7) == 0)
		return (ft_export(&root->token, env, data.outfile_fd));
	else if (ft_strncmp(root->token->cmd[0], "env", 4) == 0)
		ft_env(&root->token, env, data.outfile_fd);
	return (0);
}

void	files_case3(t_data *data)
{
	close(data->fd[1]);
	if (dup2(data->infile_fd, STDIN_FILENO) == -1)
		perror("dup out4");
	close(data->infile_fd);
}

void	files_case2(t_data *data)
{
	if (data->redout)
	{
		if (dup2(data->outfile_fd, STDOUT_FILENO) == -1)
			perror("dup out1");
		close(data->outfile_fd);
	}
	else if (data->type == PIPE_L)
	{
		close(data->fd[0]);
		if (dup2(data->outfile_fd, STDOUT_FILENO) == -1)
			perror("dup out3");
		close(data->outfile_fd);
	}
	if (data->redin)
	{
		if (dup2(data->infile_fd, STDIN_FILENO) == -1)
			perror("dup out2");
		close(data->infile_fd);
	}
	else if (data->type == PIPE_R)
		files_case3(data);
}

void	handle_files(t_data *data)
{
	if (data->type == PIPE_LR)
	{
		close(data->i);
		if (dup2(data->infile_fd, STDIN_FILENO) == -1)
			perror("dup out4");
		close(data->infile_fd);
		close(data->fd[0]);
		if (dup2(data->outfile_fd, STDOUT_FILENO) == -1)
			perror("dup out3");
		close(data->outfile_fd);
	}
	else if (data->type == PIPE_RL)
	{
		close(data->i);
		if (dup2(data->outfile_fd, STDOUT_FILENO) == -1)
			perror("dup out3");
		close(data->outfile_fd);
		close(data->fd[1]);
		if (dup2(data->infile_fd, STDIN_FILENO) == -1)
			perror("dup out4");
		close(data->infile_fd);
	}
	else
		files_case2(data);
}
