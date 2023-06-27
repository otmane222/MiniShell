/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:08:56 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/26 17:49:16 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"

typedef struct s_fds
{
	int				fd;
	int				flag;
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

int		execute_cmd(t_tree *root, t_data data, t_env **env, t_fds **list);
int		handle_here_doc(t_tree *root, t_data data, t_env **env, t_fds **list);
int		redouthanlde(t_tree *root, t_data data, t_env **env, t_fds **list);
int		append(t_tree *root, t_data data, t_env **env, t_fds **list);
int		handle_red_in(t_tree *root, t_data data, t_env **env, t_fds **list);
int		d_pipe_handle(t_tree *root, t_data data, t_env **env, t_fds **list);
int		pipe_handle(t_tree *root, t_data data, t_env **env, t_fds **list);
int		handle_command(t_tree *root, t_data data, t_env **env, t_fds **list);
int		handle_and(t_tree *root, t_data data, t_env **env, t_fds **list);
char	*ft_getenv(char *var, t_env *env);
char	*get_next_line(int fd);

t_fds	*init_list(int fd);
void	add_b_list(t_fds **lst, t_fds *neud);
void	free_fds(t_fds *list);
void	handle_files(t_data *data);

// built-in //
int		ft_export(t_rock **rock, t_env **env, int outfile);
void	ft_env(t_rock **rock, t_env **env, int outfile);
int		ft_unset(t_rock **rock, t_env **env);
int		ft_pwd(int outfile, t_env **env, char *save);
void	ft_echo(int outfile, char **arg);
int		ft_cd(char *path, t_env **env, int outfile);
int		ft_exit(t_tree *root);
int		built_in(char *str, char **cmds, t_env **env);
int		run_built_in(t_tree *root, t_data data, t_env **env);

char	**change_env(t_env *env);
char	*last_arg(char	**cmds);
char	*handle_wildcard_char(char *line);
void	edit_env(char *var, char *val, t_env **env);
void	execute_execve(char *cmd, char **cmds, t_env *env, t_fds *list);
void	child_execute(t_tree *root, t_data data, t_env **env, t_fds **list);

char	*expand_line(char *line, t_env *our_env);
char	*check_path(char **paths, char *path);
char	*deleted_q(char *line);
void	case_directory(char *str);
void	update_root(t_tree **root);
int		is_red(int a);
int		openfiles(t_tree *root, t_data *data, t_env *env, t_fds **list);
int		open_red(t_tree *root, t_env *env, int type);
void	full_list(t_fds **list, t_data *data);
int		short_cut4(t_tree *root, char *tmp, char *str, t_env *env);
int		open_rest(t_tree *root, int type);
int		continue_open(t_tree *tmp2, t_tree *tmp, t_data *data, t_env *env);

#endif