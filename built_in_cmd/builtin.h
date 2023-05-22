/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:33:47 by oaboulgh          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/17 14:55:59 by nakebli          ###   ########.fr       */
=======
/*   Updated: 2023/05/16 18:37:07 by nakebli          ###   ########.fr       */
>>>>>>> 5b403648007d759a46feb40e78a8dc3ec22f6161
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
<<<<<<< HEAD
void	ft_env(t_rock **rock, t_env **env);
=======
>>>>>>> 5b403648007d759a46feb40e78a8dc3ec22f6161

#endif
