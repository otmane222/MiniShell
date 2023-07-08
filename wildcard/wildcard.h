/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:40:11 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/05 16:06:43 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "../minishell.h"

typedef struct s_filename
{
	char				*name;
	int					counter;
	int					usable;
	struct s_filename	*next;
}	t_filename;

t_filename	*init_t_file(void);
t_filename	*get_files_name(char *line, int *flag);
t_token		*init_token_wild(void);

void		check_first_char(t_token *tok, t_var *var);
void		free_all3(t_var *var, t_filename *files);
void		skip_chars(char *line, int *j, int *i);
void		skip_q(char *line, int *i, char c);
void		skip_najmat(char *line, int *j);
void		del_tokenx(t_token **tok);
void		inti_var_to_0(t_var *var);
void		init_var_2(t_var **var);
void		skip_stars(char *line, t_var *var);
void		search_for_same_files(char **to_find, \
				t_filename *files, t_var *var);
void		make_list(t_token **head, t_token **tmp, \
				t_filename *files, t_var *var);
void		add_wildcard_to_list(t_token **tok, t_token **head, \
			t_token *tmp, t_var *var);

char		*ft_strreplace1(char *str, char *token, int len, int index);
char		*store_datas(char *str, char *line, t_var *va, t_var *var);
char		*store_datad(char *str, char *line, t_var *va, t_var *var);
char		**to_find_str(char *line, t_var *var);
char		*chars(char *line, t_var *var);
char		*ft_strfind(const char *big, const char *little, \
			size_t len, int stp);

int			found_it(const char *big, const char *little, size_t len);
int			short_cut(char *line, t_var *var, t_var *va);
int			num_of_char(char *line);
int			is_white_space(char c);
int			is_valid(int a);
int			is_valid(int a);
int			is_operator2(char c);
int			is_not_q(char *line, int *j);

#endif
