/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:23:23 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/17 17:38:37 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../minishell.h"

void	expand_tokens(t_token *token, int *i, int k, t_var *var);
char	*ft_strreplace_no_q(char *str, char *token, char *s, int index);
char	*ft_strreplace(char *str, char *token, char *s, int index);
char	*ft_strreplace_non(char *token, char *s, int index);
char	*get_env_var(char *s);
char	*ft_getenv(char *var, t_env *env);
char	*expand_line(char *line, t_env *our_env);

#endif