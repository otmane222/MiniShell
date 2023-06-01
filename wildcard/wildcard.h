/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:40:11 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/01 17:44:32 by oaboulgh         ###   ########.fr       */
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

void	init_var_2(t_var **var);
void	store_datas(char **str, char *line, int *i, int *j);
void	store_datad(char **str, char *line, int *i, int *j);
char	*ft_strreplace_no_q(char *str, char *token, int len, int index);
int		found_it(const char *big, const char *little, size_t len);

#endif
