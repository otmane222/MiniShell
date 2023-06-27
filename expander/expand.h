/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:23:23 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/25 16:29:15 by oaboulgh         ###   ########.fr       */
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
char	*continue_expand(char *line, t_env *our_env);
char	*handle_tild(char *line, t_env *our_env);

char	*check_str(char *line, t_env *our_env, int *start);
char	*ft_strreplace_no_q2(char *str, char *token, char *s, int index);
char	*str_full(char *str, char *ret, int *flag, int *j);
int		num_op(char *str);
char	*helpful_call2(char *line, int *start, t_env *our_env);

void	skip_char(char *line, int *start);
void	skip_until(char *line, int *start);
void	skip_in_q(char *line, int *start, char stop);

int		is_white_space(char c);
int		char_type(char c);
int		is_operator(char c);
void	skip_spaces(char *line, int *start);
int		is_qoutes(char c);

char	*questio_mark(char *line, int *start);

#endif