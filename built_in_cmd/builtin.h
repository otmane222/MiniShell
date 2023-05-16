/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:33:47 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/16 18:37:07 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"
# include "../envirenment/env.h"

void	pwd(int outfile);
void	ft_export(t_rock **rock, t_env **env);
void	ft_unset(t_rock **rock, t_env **env);
void	builtin_cmds(t_rock **rock, t_env **env);

#endif
