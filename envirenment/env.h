/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/05/17 14:42:12 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/17 16:52:06 by nakebli          ###   ########.fr       */
=======
/*   Created: 2023/05/10 15:23:44 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/15 16:32:11 by nakebli          ###   ########.fr       */
>>>>>>> 5b403648007d759a46feb40e78a8dc3ec22f6161
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../minishell.h"

// env.c functions
t_env	*put_env_to_new(char **env);
char	*get_key(char *line);
char	*get_value(char *line);
// env_utils.c functions
t_env	*ft_lstlast_env(t_env *lst);
t_env	*ft_lstnew_env(char *value, char *key);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
<<<<<<< HEAD
void	ft_lstdelone_env1(t_env **env, t_env **head);
=======
char	*get_key(char *line);
char	*get_value(char *line);
>>>>>>> 5b403648007d759a46feb40e78a8dc3ec22f6161

#endif