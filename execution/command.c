/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:30:46 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/11 18:58:49 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*check_path(char **paths, char *path)
{
	int		i;
	char	*save;
	char	*tmp;

	i = 0;
	if (!paths)
		ft_printf("minishell: %s: No such file or directory\n", path);
	if (access(path, X_OK) == 0)
		return (path);
	save = path;
	path = ft_strjoin("/", path);
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], path);
		free (tmp);
		tmp = NULL;
		if (access(paths[i], X_OK) == 0)
			return (free(path), paths[i]);
		i++;
	}
	return (save);
}

int	built_in(char *str)
{
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
		return (ft_pwd(data.outfile_fd, env, 0));
	else if (ft_strncmp(root->token->cmd[0], "echo", 5) == 0)
		ft_echo(data.outfile_fd, root->token->cmd);
	else if (ft_strncmp(root->token->cmd[0], "cd", 3) == 0)
		return (ft_cd(root->token->cmd[1], env));
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
		{
			close(data->fd[1]);
			if (dup2(data->infile_fd, STDIN_FILENO) == -1)
				perror("dup out4");
			close(data->infile_fd);
		}
	}
}

void	case_directory(char *str)
{
	DIR		*k;

	k = opendir(str);
	if (k)
	{
		ft_printf("Minishell: %s: is directory\n", \
			str);
		exit (126);
	}
}

void	execute_execve(char *cmd, char **cmds, t_env *env)
{
	char	**our_env;

	(void)env;
	our_env = change_env(env);
	execve(cmd, cmds, our_env);
	free_2dd(our_env);
	if (errno == ENOENT)
	{
		ft_printf("Minishell: %s: command not found\n", cmd);
		exit (127);
	}
	exit (1);
}

int	wait_last_cmd(t_data data)
{
	waitpid(data.i, &data.status, 0);
	g_exit_status = WEXITSTATUS(data.status);
	if (data.status)
		return (runnig_cmd(0), 1);
	return (runnig_cmd(0), 0);
}

void	expander_in_execution(t_rock *rock, t_env **env)
{
	int	i;

	i = 0;
	while (rock->cmd[i])
	{
		if (rock->arr[i] != -9)
			rock->cmd[i] = expand_line(rock->cmd[i], *env);
		i++;
	}
	i = 0;
	while (rock->cmd[i])
	{
		if (rock->arr[i] != -9)
			rock->cmd[i] = deleted_q(rock->cmd[i]);
		i++;
	}
}

int	handle_command(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	char	**paths;
	char	*cmd;

	(void)list;
	runnig_cmd(1);
	if (stop_execution(-1) == -2)
		return (runnig_cmd(0), stop_execution(0), 1);
	expander_in_execution(root->token, env);
	if (built_in(root->token->cmd[0]))
		return (runnig_cmd(0), run_built_in(root, data, env));
	data.i = fork();
	if (data.i < 0)
		return (perror("fork"), 1);
	if (data.i == 0)
	{
		handle_files(&data);
		paths = ft_split(ft_getenv("PATH", *env), ':');
		case_directory(root->token->cmd[0]);
		cmd = check_path(paths, root->token->cmd[0]);
		execute_execve(cmd, root->token->cmd, *env);
	}
	if (root->token->is_last)
		return (wait_last_cmd(data));
	return (0);
}
