/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:31:18 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/26 21:08:25 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

void	put_type_of_tokens(t_token *tmp);
int		func5(t_token *token);
int		func6(t_token *token);
int		is_op(int a);
int		is_red(int a);

#endif