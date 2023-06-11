/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:42:12 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/10 15:45:41 by oaboulgh         ###   ########.fr       */
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
void	ft_lstdelone_env1(t_env **env, t_env **head);
int		ft_pwd(int outfile, __attribute__((unused)) t_env **env, int flag);

#endif