/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:42:12 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/24 08:42:02 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../minishell.h"

// env.c functions
t_env	*put_env_to_new(char **env);
char	*get_key(char *line);
char	*ft_getenv(char *var, t_env *env);
char	*get_value(char *line);
// env_utils.c functions
t_env	*ft_lstlast_env(t_env *lst);
t_env	*ft_lstnew_env(char *value, char *key);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_lstdelone_env1(t_env **env, t_env **head);

#endif