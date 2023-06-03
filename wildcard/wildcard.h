/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:40:11 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/03 16:10:42 by oaboulgh         ###   ########.fr       */
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

void		init_var_2(t_var **var);
char		*store_datas(char *str, char *line, int *i, int *j);
// void	store_datad(char **str, char *line, int *i, int *j);
char		*ft_strreplace1(char *str, char *token, int len, int index);
int			found_it(const char *big, const char *little, size_t len);

t_filename	*init_t_file(void);
t_filename	*get_files_name(void);
char		*ft_strfind(const char *big, const char *little, \
			size_t len, int stp);
// int			there_is(char *to_find, char *str, t_var *var);
void		del_tokenx(t_token **tok);
void		inti_var_to_0(t_var *var);
void		skip_q(char *line, int *i, char c);
void		search_for_same_files(char **to_find, \
				t_filename *files, t_var *var);
char		*store_datas(char *str, char *line, int *i, int *j);
void		skip_najmat(char *line, int *j);
void		skip_chars(char *line, int *j, int *i);
int			num_of_char(char *line);

int			is_white_space(char c);
int			is_operator(char c);

#endif
