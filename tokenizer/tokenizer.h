/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:22:23 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/30 12:09:09 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../minishell.h"

void	get_token(t_lexer *lex, char *line);
t_token	*init_token(size_t x);
int		first_step(t_token **token, char *line, t_var *var);

void	handle_squotes(char *line, t_var *var, t_token **token, int *i);
void	handle_dquotes(char *line, t_var *var, t_token **token, int *i);
void	handle_chars(char *line, t_var *var, t_token **token, int *i);
void	handle_spaces(char *line, t_var *var, t_token **token, int *i);
void	handle_seperators(char *line, t_var *var, t_token **token, int *i);

void	stor_data(t_token **t, char *line, t_var *var, char *stop);
void	next_node(t_token **t, char *line, int *i);

int		char_type(char c);
int		is_white_space(char c);
int		is_operator(char c);
int		is_qoutes(char c);
int		is_char(char c);

#endif