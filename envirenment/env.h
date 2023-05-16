/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:23:44 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/15 16:32:11 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../minishell.h"

t_env	*init_env(void);
t_env	*ft_lstlast_env(t_env *lst);
t_env	*ft_lstnew_env(char *value, char *key);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
char	*get_key(char *line);
char	*get_value(char *line);

#endif