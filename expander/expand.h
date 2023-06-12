/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:23:23 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/30 14:30:39 by oaboulgh         ###   ########.fr       */
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

void	skip_char(char *line, int *start);
void	skip_in_q(char *line, int *start, char stop);

int		is_white_space(char c);
int		char_type(char c);
int		is_operator(char c);

#endif