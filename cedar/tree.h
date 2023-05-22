/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:43:02 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/21 19:07:49 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "../minishell.h"

//ASTs
t_tree	*ast_pipe(t_rock *tok);
t_tree	*ast_and_or(t_rock *tok);
t_tree	*ast_parenthese(t_rock *rock);
t_tree	*ast_redirections(t_rock *tok);

t_tree	*init_tree(void);
void	get_head(t_rock **head);
void	init_var_2(t_var **var);
void	del_token(t_rock *tok);
int		is_red(int a);
// cases AST_utils
t_tree	*case_no_next(t_rock *begin, t_rock *tok, t_rock *b, t_tree *tree);
t_tree	*case_no_perv(t_rock *begin, t_rock *tok, t_rock *b, t_tree *tree);
t_tree	*case_nothing(t_rock *begin, t_rock *tok, t_tree *tree);
t_tree	*case_both_exit(t_rock *begin, t_rock *tok, t_rock *b, t_tree *tree);

#endif