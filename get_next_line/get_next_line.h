/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:22:56 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/01 12:30:20 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_l {
	char		*text;
	struct s_l	*next;
}	t_l;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
int		ft_strchr3(t_l *head);
void	ft_malloc(t_l *head, char **line);
t_l		*ft_lstlast3(t_l *lst);
void	free_node(t_l **lst, void (*del)(void*));

#endif