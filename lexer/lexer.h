/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:17:03 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/12 14:18:14 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

// void	lex_tokens(t_lexer *lex);
void	get_type(t_token *t);
void	join_cmd(t_token *tmp, t_token *token, t_var *var, int *g);
void	small_call(t_token *tmp, t_token *token);
void	join_cmd_and_arg(t_lexer *lex);

#endif