/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:33:47 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/24 11:30:33 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"
# include "../envirenment/env.h"

void	ft_env(t_rock **rock, t_env **env, int outfile);
void	ft_lstdelone_env1(t_env **env, t_env **head);
void	builtin_cmds(t_rock **rock, t_env **env);
void	ft_export(t_rock **rock, t_env **env);
void	ft_unset(t_rock **rock, t_env **env);
void	ft_echo(int outfile, char **arg);
int		ft_exit(t_tree *root);
int		ft_cd(char *path);
void	ft_pwd(int outfile);

#endif
