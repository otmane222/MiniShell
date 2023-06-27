/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 03:03:00 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/27 03:51:40 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

t_rock	*get_last(t_rock *rock)
{
	if (!rock)
		return (NULL);
	if (!rock->next)
		return (rock);
	while (rock->next && rock->next->flag)
		rock = rock->next;
	return (rock);
}

static char	*helpful_call(char *line, int *start, t_env *our_env)
{
	char	*s;
	char	*str;

	if (line[*start] == '?')
		return (questio_mark(line, start));
	s = get_env_var(&line[(*start)]);
	str = ft_getenv(s, our_env);
	if (str)
	{
		line = ft_strreplace_no_q(str, line, s, (*start));
		(*start) = (*start) + ft_strlen(str) - 1;
	}
	else
	{
		line = ft_strreplace_non(line, s, (*start));
		(*start) = (*start) - 1;
	}
	free(str);
	free(s);
	while (line[(*start)] && line[(*start)] != '$' && \
	line[(*start)])
		(*start)++;
	return (line);
}

char	*expand_here_doc(char *line, t_env *our_env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '$')
		{
			j++;
			if (j == 2)
				j = 0;
		}
		while (line[i] == '\'' || line[i] == '\"')
		{
			j = 1;
			i++;
		}
		if (line[i] && line[i] != '$' && j == 1)
			line = helpful_call(line, &i, our_env);
		if (!line[i])
			break ;
		i++;
	}
	return (line);
}

void	loop_and_stock(t_tree *tree, t_env *env, int fd)
{
	char	*str;

	while (1)
	{
		if (stop_execution(-1) != -2)
			write(1, "> ", 3);
		str = get_next_line(STDIN_FILENO);
		if (str == NULL)
			break ;
		if (ft_strncmp(str, tree->token->next->cmd[0], \
			ft_strlen(str) - 1) == 0 && \
			ft_strlen(str) - 1 == ft_strlen(tree->token->next->cmd[0]))
			break ;
		if (tree->token->next->expand)
			str = expand_here_doc(str, env);
		ft_putstr_fd(str, fd);
		free(str);
		str = NULL;
	}
	free(str);
}

void	write_in_here_doc(t_tree *tree, t_env *env)
{
	char		*str1;
	char		*tmp;
	static int	i = 0;
	int			fd;

	fd = 0;
	i++;
	str1 = ft_itoa(i);
	tmp = str1;
	str1 = ft_strjoin("/tmp/temp_file", str1);
	free(tmp);
	fd = open(str1, O_RDWR | O_CREAT | O_TRUNC, 0655);
	if (fd == -1)
		printf ("Error opening :%s\n", str1);
	tree->token->next->cmd[0] = \
		handle_case(tree->token->next->cmd[0]);
	tree->token->next->cmd[0] = \
		deleted_q(tree->token->next->cmd[0]);
	is_there_here_doc(1);
	loop_and_stock(tree, env, fd);
	free_2dd(tree->token->next->cmd);
	tree->token->next->cmd = malloc(sizeof(char *) * 2);
	tree->token->next->cmd[0] = str1;
	tree->token->next->cmd[1] = NULL;
	close(fd);
}
