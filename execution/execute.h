/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:08:56 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/24 21:38:32 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"

typedef struct s_data
{
	int		fd[2];
	int		fd_here_doc;
	int		fd_red;
	int		fd_append;
	int		fd_red_in;
	int		infile_fd;
	int		outfile_fd;
	int		i;
	int		j;
	int		status;
}	t_data;

int		execute_cmd(t_tree *root, int infile_fd, int outfile_fd, t_env **env);
int		handle_here_doc(t_tree *root, t_data data, t_env **env);
int		red_out_hanlde(t_tree *root, t_data data, t_env **env);
int		handle_append(t_tree *root, t_data *data, t_env **env);
int		handle_red_in(t_tree *root, t_data *data, t_env **env);
int		d_pipe_handle(t_tree *root, t_data *data, t_env **env);
int		pipe_handle(t_tree *root, t_data *data, t_env **env);
int		handle_command(t_tree *root, t_data *data, t_env **env);
int		handle_and(t_tree *root, t_data *data, t_env **env);
char	*ft_getenv(char *var, t_env *env);
char	*get_next_line(int fd);

// built-in //
void	ft_env(t_rock **rock, t_env **env, int outfile);
void	ft_export(t_rock **rock, t_env **env);
void	ft_unset(t_rock **rock, t_env **env);
void	ft_echo(int outfile, char **arg);
int		ft_exit(t_tree *root);
int		ft_cd(char *path);
void	ft_pwd(int outfile);

#endif