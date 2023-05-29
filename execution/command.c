/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:30:46 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/29 22:56:43 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*check_path(char **paths, char *path)
{
	int		i;

	i = 0;
	if (!path || path[0] == '\0')
		return (NULL);
	if (access(path, X_OK) == 0)
		return (path);
	path = ft_strjoin("/", path);
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], path);
		if (access(paths[i], X_OK) == 0)
			return (paths[i]);
		i++;
	}
	return (NULL);
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
		ft_pwd(data.outfile_fd);
	else if (ft_strncmp(root->token->cmd[0], "echo", 5) == 0)
		ft_echo(data.outfile_fd, root->token->cmd);
	else if (ft_strncmp(root->token->cmd[0], "cd", 3) == 0)
		return (ft_cd(root->token->cmd[1], env));
	else if (ft_strncmp(root->token->cmd[0], "exit", 5) == 0)
		ft_exit(root);
	else if (ft_strncmp(root->token->cmd[0], "unset", 6) == 0)
		return (5);
	else if (ft_strncmp(root->token->cmd[0], "export", 7) == 0)
		ft_export(&root->token, env);
	else if (ft_strncmp(root->token->cmd[0], "env", 4) == 0)
		ft_env(&root->token, env, data.outfile_fd);
	return (0);
}

int	handle_command(t_tree *root, t_data data, t_env **env, t_fds *list)
{
	char	**paths;
	char	*cmd;
	DIR 	*k;

	(void)list;
	if (built_in(root->token->cmd[0]))
		return (run_built_in(root, data, env));
	else
	{
		data.i = fork();
		if (data.i == 0)
		{
			if (data.type == RED_OUT)
			{
				if (dup2(data.outfile_fd, STDOUT_FILENO) == -1)
					perror("dup out");
				close(data.outfile_fd);
			}
			else if (data.type == RED_IN)
			{
				if (dup2(data.infile_fd, STDIN_FILENO) == -1)
					perror("dup out");
				close(data.infile_fd);
			}
			else if (data.type == PIPE_L)
			{
				close(data.fd[0]);
				if (dup2(data.outfile_fd, STDOUT_FILENO) == -1)
					perror("dup out");
				close(data.outfile_fd);
			}
			else if (data.type == PIPE_R)
			{
				close(data.fd[1]);
				if (data.outfile_fd != 1)
				{
					if (dup2(data.outfile_fd, STDOUT_FILENO) == -1)
						perror("dup out");
					close(data.outfile_fd);
				}
			}
			if (data.infile_fd != 0)
			{
				if (data.outfile_fd != 1)
					close(data.outfile_fd);
				if (dup2(data.infile_fd, STDIN_FILENO) == -1)
					perror("dup in");
				close(data.infile_fd);
			}
			paths = ft_split(ft_getenv("PATH", *env), ':');
			k = opendir(root->token->cmd[0]);
			if (k)
			{
				ft_printf("Minishell: %s: is directory\n", \
					root->token->cmd[0]);
				exit (126);
			}
			cmd = check_path(paths, root->token->cmd[0]);
			if (!cmd)
			{
				ft_printf("Minishell: %s: command not found\n", \
					root->token->cmd[0]);
				exit (127);
			}
			execve(cmd, root->token->cmd, paths);
			perror("command");
			exit(1);
		}
		if (root->token->is_last)
		{
			waitpid(data.i, &data.status, 0);
			g_exit_status = WEXITSTATUS(data.status);
			if (data.status)
				return (1);
		}
	}
	return (0);
}
