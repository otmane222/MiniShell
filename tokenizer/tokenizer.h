/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:07:37 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/23 12:07:37 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../minishell.h"

int		first_step(t_token **token, char *line, t_var *var);

void	handle_squotes(char *line, t_var *var, t_token **token, int *i);
void	handle_dquotes(char *line, t_var *var, t_token **token, int *i);
void	handle_chars(char *line, t_var *var, t_token **token, int *i);
void	handle_spaces(char *line, t_var *var, t_token **token, int *i);
void	handle_seperators(char *line, t_var *var, t_token **token, int *i);
void	handle_parenthese(char *line, t_var *var, t_token **token, int *i);

t_token	*init_token(size_t x);
void	next_node(t_token **t, char *line, int *i);
void	del_node(t_token *token);
void	init_var(t_var **var);
void	get_head_token(t_token **token);

int		char_type(char c);
int		is_operator(char c);
int		is_qoutes(char c);
int		is_char(char c);
int		is_parenthese(char c);
int		is_white_space(char c);

char	*expand_line2(char *line, t_env *env);
void	wild_card_handle(t_token **token);
void	del_q(t_token **token);
char	*store_dq(char *str, char *line, int *i, int *j);
char	*store_sq(char *str, char *line, int *i, int *j);

#endif