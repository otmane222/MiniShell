/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:08:56 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/04 00:09:55 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"

typedef struct s_fds
{
	int				fd;
	struct s_fds	*next;
}	t_fds;

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
	int		redin;
	int		redout;
	int		type;
	int		status;
}	t_data;


int		execute_cmd(t_tree *root, t_data data, t_env **env, t_fds *list);
int		handle_here_doc(t_tree *root, t_data data, t_env **env, t_fds *list);
int		red_out_hanlde(t_tree *root, t_data data, t_env **env, t_fds *list);
int		handle_append(t_tree *root, t_data data, t_env **env, t_fds *list);
int		handle_red_in(t_tree *root, t_data data, t_env **env, t_fds *list);
int		d_pipe_handle(t_tree *root, t_data data, t_env **env, t_fds *list);
int		pipe_handle(t_tree *root, t_data data, t_env **env, t_fds *list);
int		handle_command(t_tree *root, t_data data, t_env **env);
int		handle_and(t_tree *root, t_data data, t_env **env, t_fds *list);
char	*ft_getenv(char *var, t_env *env);
char	*get_next_line(int fd);

t_fds	*init_list(int fd);
void	add_b_list(t_fds **lst, t_fds *neud);
void	free_fds(t_fds *list);

// built-in //
void	ft_export(t_rock **rock, t_env **env, int outfile);
void	ft_env(t_rock **rock, t_env **env, int outfile);
void	ft_unset(t_rock **rock, t_env **env);
void	ft_pwd(int outfile, t_env **env);
void	ft_echo(int outfile, char **arg);
int		ft_cd(char *path, t_env **env);
int		ft_exit(t_tree *root);

char	*expand_line(char *line, t_env *our_env);
char	*check_path(char **paths, char *path);
char	*deleted_q(char *line);

#endif