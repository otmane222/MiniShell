/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:41:58 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/11 12:02:48 by oaboulgh         ###   ########.fr       */
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
	if (root && root->token->type == FILE)
	{
		fd = open(root->token->cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0655);
		if (fd == -1)
		{
			printf ("Error opening :%s\n", root->token->cmd[0]);
			return (1);
		}
		return (fd);
	}
	return (0);
}

int	fd_to_out_append(t_tree *root)
{
	int	fd;

	root = root->right;
	while (root->left)
		root = root->left;
	if (root->token->type == FILE)
	{
		fd = open(root->token->cmd[0], O_RDWR | O_CREAT | O_APPEND, 0655);
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
	return (0);
}

void	ft_putstr2(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	fd_to_here_doc(t_tree *root)
{
	int			fd;
	char		*str;
	// struct stat	sfile;

	// stat("Makefile", &sfile);
	root = root->right;
	while (root->left)
		root = root->left;
	if (root->token->type == LIMITER)
	{
		fd = open("/tmp/temp_file", O_RDWR | O_CREAT | O_TRUNC, 0655);
		if (fd == -1)
		{
			printf ("Error opening :%s\n", "/tmp/temp_file");
			return (1);
		}
		while (1)
		{
			write(1, "pipe heredoc> ", 15);
			str = get_next_line(STDIN_FILENO);
			if (ft_strncmp(str, root->token->cmd[0], \
				ft_strlen(root->token->cmd[0])) == 0)
				break ;
			if (str == NULL)
				break ;
			ft_putstr2(fd, str);
			free(str);
		}
		// close(fd);
		free(str);
		str = NULL;
		return (fd);
	}
	return (1);
}

int	check_root(t_tree *root)
{
	if ((root->token->type == FILE || (root->token->type == LIMITER)) && (!root->left && !root->right))
		return (1);
	return (0);
}

int	execute_cmd(t_tree *root, int infile_fd, int outfile_fd, char **env)
{
	char	**paths;
	char	*cmd;
	int		fd[2];
	int		status;
	int		i;
	int		j;
	int		stat;

	if (!root || check_root(root))
		return (0);
	if (root->token->type == PIPE)
	{
		if (pipe(fd) == -1)
			perror ("pipe error");
		status = execute_cmd(root->left, infile_fd, fd[1], env);
		if (status == 1)
			return (1);
		close (fd[1]);
		status = execute_cmd(root->right, fd[0], outfile_fd, env);
		if (status == 1)
			return (1);
		close (fd[0]);
	}
	else if (root->token->type == RED_OUT)
	{
		j = fd_to_out(root);
		if (j == -1)
			printf("Error opening file\n");
		status = execute_cmd(root->left, infile_fd, j, env);
		if (status == 1)
			return (1);
		status = execute_cmd(root->right, infile_fd, outfile_fd, env);
		if (status == 1)
			return (1);
	}
	else if (root->token->type == D_RED_OUT)
	{
		j = fd_to_out_append(root);
		if (j == -1)
			printf("Error opening file\n");
		status = execute_cmd(root->left, infile_fd, j, env);
		if (status == 1)
			return (1);
		status = execute_cmd(root->right, infile_fd, outfile_fd, env);
		if (status == 1)
			return (1);
	}
	else if (root->token->type == RED_IN)
	{
		j = fd_to_in(root);
		if (j == -1)
			printf("Error opening file\n");
		status = execute_cmd(root->left, j, outfile_fd, env);
		if (status == 1)
			return (1);
		status = execute_cmd(root->right, infile_fd, outfile_fd, env);
		if (status == 1)
			return (1);
	}
	else if (root->token->type == DPIPE)
	{
		status = execute_cmd(root->left, infile_fd, outfile_fd, env);
		if (status == 1)
		{
			status = execute_cmd(root->right, infile_fd, outfile_fd, env);
			if (status == 1)
				return (1);
		}
		else
			return (0);
	}
	else if (root->token->type == D_AND)
	{
		status = execute_cmd(root->left, infile_fd, outfile_fd, env);
		if (status == 1)
			return (1);
		status = execute_cmd(root->right, infile_fd, outfile_fd, env);
		if (status == 1)
			return (1);
	}
	else if (root->token->type == D_RED_IN)
	{
		j = fd_to_here_doc(root);
		if (j == -1)
			printf("Error opening file\n");
		j = open("/tmp/temp_file", O_RDONLY | O_EXCL, 0655);
		status = execute_cmd(root->right, infile_fd, outfile_fd, env);
		if (status == 1)
			return (1);
		status = execute_cmd(root->left, j, outfile_fd, env);
		if (status == 1)
			return (1);
		unlink("temp_file");
	}
	else if (root->token->type == CMD)
	{
		i = fork();
		if (i == 0)
		{
			if (infile_fd != 0)
			{
				if (dup2(infile_fd, 0) == -1)
					perror("dup in");
			}
			if (outfile_fd != 1)
			{
				if (dup2(outfile_fd, 1) == -1)
					perror("dup out");
			}
			paths = get_env(env);
			cmd = check_path(paths, root->token->cmd[0]);
			if (execve(cmd, root->token->cmd, NULL) == -1)
				perror("command");
			free_2dd(paths);
			exit(1);
		}
		else
		{
			waitpid(i, &stat, 0);
			if (stat)
				return (1);
		}
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

	if (execute_cmd(root, 0, 1, env) == 1)
		printf ("Error During Execution\n");
}
