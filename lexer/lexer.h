/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:31:39 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/21 18:49:49 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

int		is_red2(int a);
t_rock	*init_rock(void);
void	new_rock(t_rock **rock);
void	get_head1(t_rock **head);
void	put_type_of_tokens(t_token *tmp);
void	case_cmd_after_file(t_rock *rock);
void	case_of_arg_after_file(t_rock *rock);
void	join_2d_arrs(t_rock *rock, t_rock *tmp);
void	join_arg_with_cmd(t_rock *rock, t_token *token);

#endif
