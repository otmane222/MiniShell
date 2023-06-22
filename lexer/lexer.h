/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:31:39 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/22 00:30:20 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

int		is_red2(int a);
int		is_kind(int a);
t_rock	*init_rock(void);
void	new_rock(t_rock **rock);
void	flag_cmd(t_rock *rock);
void	get_head1(t_rock **head);
void	free_tokens(t_token **token);
void	put_type_of_tokens(t_token *tmp);
void	handle_followed_red(t_rock *rock);
void	case_cmd_after_file(t_rock *rock);
void	case_of_arg_after_file(t_rock *rock);
void	swap_token_char(t_rock **a, t_rock **b);
void	join_2d_arrs(t_rock *rock, t_rock *tmp);
void	join_arg_with_cmd(t_rock *rock, t_token *token);

#endif
