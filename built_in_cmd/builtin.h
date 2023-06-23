/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:02:18 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/23 12:02:21 by nakebli          ###   ########.fr       */
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
int		check_arguments(char *key, int i);
void	ft_echo(int outfile, char **arg);
void	print_error2(int i, char *str);
int		ft_cd(char *path, t_env **env, int outfile);
int		ft_exit(t_tree *root);
void	print_error(int i);

#endif
