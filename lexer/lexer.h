/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:31:39 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/08 21:34:26 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

void	get_type(t_token *t);
void	get_type_small_call(t_token *t);
void	get_type1(t_rock *t);
void	get_type_small_call1(t_rock *t);

void	expand_tokens(t_token *token, int *i, int k, t_var *var);

void	case_cmd_after_file(t_rock *rock);
void	case_of_arg_after_file(t_rock *rock);

void	del_rock3(t_rock *rock);
void	free_2dd(char **str);

#endif