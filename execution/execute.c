/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:41:58 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/30 20:55:13 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*check_path(char **paths, char *path)
{
	int		i;

	i = 0;
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

char	**get_env(char **env)
{
	int		i;
	char	*str;
	char	**rtn;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 5))
			break ;
		i++;
	}
	if (env[i])
	{
		str = env[i] + 5;
		rtn = ft_split(str, ':');
		return (rtn);
	}
	return (NULL);
}

int	fd_to_out(t_tree *root)
{
	int	fd;

	root = root->right;
	while (root->left)
		root = root->left;
	if (root->token->type == FILE)
	{
		fd = open(root->token->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
		{
			printf ("Error opening :%s\n", root->token->cmd[0]);
			return (1);
		}
		return (fd);
	}
	return (1);
}

int	fd_to_in(t_tree *root)
{
	int	fd;

	root = root->right;
	while (root->left)
		root = root->left;
	if (root->token->type == FILE)
	{
		fd = open(root->token->cmd[0], O_RDONLY, 0655);
		if (fd == -1)
		{
			printf ("Error opening :%s\n", root->token->cmd[0]);
			return (1);
		}
		return (fd);
	}
	return (1);
}

int	execute_cmd(t_tree *root, int infile_fd, int outfile_fd, char **env)
{
	char	**paths;
	char	*cmd;
	int		fd[2];
	int		status;
	int		i;
	int		j;

	if (!root)
		return (1);
	if (root->token->type == PIPE)
	{
		if (pipe(fd) == -1)
			perror ("pipe error");
		status = execute_cmd(root->left, infile_fd, fd[1], env);
		if (status == -1)
			return (-1);
		close (fd[1]);
		status = execute_cmd(root->right, fd[0], outfile_fd, env);
		if (status == -1)
			return (-1);
		close (fd[0]);
	}
	else if (root->token->type == RED_OUT)
	{
		j = fd_to_out(root);
		if (j == -1)
			printf("Error opening file\n");
		status = execute_cmd(root->left, infile_fd, j, env);
		if (status == -1)
			return (-1);
		status = execute_cmd(root->right, infile_fd, outfile_fd, env);
		if (status == -1)
			return (-1);
	}
	else if (root->token->type == RED_IN)
	{
		j = fd_to_in(root);
		if (j == -1)
			printf("Error opening file\n");
		status = execute_cmd(root->left, j, outfile_fd, env);
		if (status == -1)
			return (-1);
		status = execute_cmd(root->right, infile_fd, outfile_fd, env);
		if (status == -1)
			return (-1);
	}
	else if (root->token->type == CMD)
	{
		i = fork();
		if (i == 0)
		{
			if (dup2(infile_fd, 0) == -1)
				perror("dup in");
			if (dup2(outfile_fd, 1) == -1)
				perror("dup out");
			paths = get_env(env);
			cmd = check_path(paths, root->token->cmd[0]);
			if (execve(cmd, root->token->cmd, NULL) == -1)
				perror("execute");
			exit(1);
		}
		wait(NULL);
	}
	return (0);
}

void	execute(t_tree *root, char **env)
{
	pid_t	i;
	char	**path;
	char	*cmd;
	int		fd[2];
	t_tree	*rt;

	if (execute_cmd(root, 0, 1, env) == -1)
		printf ("Error During Execution\n");
}
