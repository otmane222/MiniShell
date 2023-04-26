#include "../minishell.h"
// #include <unistd.h>
// #include <stdlib.h>
#include <sys/wait.h>

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

void    execute(t_tree *root, char **env)
{
	pid_t     i;
	char    **path;
	char    *cmd;
	int		fd[2];
	t_tree  *rt;

	pipe(fd);
	
	wait(NULL);
	sleep(1);
	close(fd[0]);
	close(fd[1]);
}
/*
rt = root;
	while (root->left)
		root = root->left;
	path = get_env(env);
	if (!path)
	{
		printf("hw\n");
		return ;
	}
	i = fork();
	if (i == 0)
	{
		cmd = check_path(path, root->token->cmd[0]);
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("got here");
		}
		execve(cmd,root->token->cmd, NULL);
		exit (1);
	}
	while (rt->left->left)
		rt = rt->left;
	rt = rt->right;
	int j = fork();
	if (j == 0)
	{
		close(fd[1]);
		cmd = check_path(path, rt->token->cmd[0]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			perror("here");
		execve(cmd,rt->token->cmd, NULL);
		exit (1);
	}
*/