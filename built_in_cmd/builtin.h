/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:33:47 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/26 00:21:05 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"
# include "../envirenment/env.h"

int		ft_export(t_rock **rock, t_env **env, int outfile);
void	ft_env(t_rock **rock, t_env **env, int outfile);
void	ft_lstdelone_env1(t_env **env, t_env **head);
void	edit_env(char *var, char *val, t_env **env);
int		ft_pwd(int outfile, t_env **env, char *save);
void	builtin_cmds(t_rock **rock, t_env **env);
int		ft_unset(t_rock **rock, t_env **env);
char	*ft_getenv(char *var, t_env *env);
int		check_arguments(char *key, char *line, int i);
void	ft_echo(int outfile, char **arg);
void	print_error2(int i, char *str);
int		ft_cd(char *path, t_env **env, int outfile);
int		ft_exit(t_tree *root);
void	print_error(int i);

#endif
