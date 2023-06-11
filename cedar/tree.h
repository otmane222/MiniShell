/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:21:35 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/10 00:12:56 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "../minishell.h"

//ASTs
t_tree	*ast_pipe(t_rock *tok, t_env *env);
t_tree	*ast_and(t_rock *tok, t_env *env);
t_tree	*ast_or(t_rock *tok, t_env *env);
t_tree	*ast_parenthese(t_rock *rock, t_env *env);
t_tree	*ast_red_her_doc(t_rock *rock, t_env *env);
t_tree	*ast_reds(t_rock *tok, t_env *env);

void	skip_parenthese(t_rock **rock);
char	*get_next_line(int fd);
char	*deleted_q(char *line);

char	*store_datadd(char *str, char *line, int *i, int *j);
char	*store_datass(char *str, char *line, int *i, int *j);

t_tree	*init_tree(void);
void	get_head(t_rock **head);
void	init_var_2(t_var **var);
void	del_token(t_rock *tok);
int		is_red(int a);

#endif