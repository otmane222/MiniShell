/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:20:30 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/27 19:20:30 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "../minishell.h"

t_tree	*ast_parenthese(t_token *tok);
t_tree	*ast_parenthese(t_token *tok);
t_tree	*ast_pipe(t_token *tok);
t_tree	*ast_and_or(t_token *tok);
t_tree	*case_file(t_token *tmp, t_tree *tree);
t_tree	*ast_redirections(t_token *tok);

#endif