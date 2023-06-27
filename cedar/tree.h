/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:21:35 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/25 23:35:18 by oaboulgh         ###   ########.fr       */
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
char	*handle_case(char *line);

char	*store_datadd(char *str, char *line, int *i, int *j);
char	*store_datass(char *str, char *line, int *i, int *j);

t_tree	*init_tree(void);
void	get_head(t_rock **head);
void	init_var_2(t_var **var);
void	del_token(t_rock *tok);
int		is_red(int a);
void	get_tail(t_rock **head);
void	skip_parenthese1(t_rock **rock);
t_rock	*get_last(t_rock *rock);
int		check_red_exist(t_rock *rock, int *flag, int *i);
int		check_red_exist2(t_rock *rock, int *flag, int *i);
void	write_in_here_doc(t_tree *tree, t_env *env);
void	loop_and_stock(t_tree *tree, t_env *env, int fd);

char	*questio_mark(char *line, int *start);
char	*get_env_var(char *s);
char	*ft_getenv(char *var, t_env *env);
char	*ft_strreplace(char *str, char *token, char *s, int index);
char	*ft_strreplace_non(char *token, char *s, int index);

void	skip_char(char *line, int *start);
void	skip_until(char *line, int *start);
void	skip_in_q(char *line, int *start, char stop);

char	*ft_strreplace_no_q(char *str, char *token, char *s, int index);
#endif