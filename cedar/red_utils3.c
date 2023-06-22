/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 03:03:00 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/22 03:03:12 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

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
		if (ft_strncmp(str, tree->heredoc->token->next->cmd[0], \
			ft_strlen(str) - 1) == 0 && \
			ft_strlen(str) - 1 == ft_strlen(tree->heredoc->token->next->cmd[0]))
			break ;
		if (tree->heredoc->token->next->expand)
			str = expand_line(str, env);
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
	tree->heredoc->token->next->cmd[0] = \
		handle_case(tree->heredoc->token->next->cmd[0]);
	tree->heredoc->token->next->cmd[0] = \
		deleted_q(tree->heredoc->token->next->cmd[0]);
	is_there_here_doc(1);
	loop_and_stock(tree, env, fd);
	tree->heredoc->name = str1;
	tree->heredoc->infile_fd = fd;
	close(fd);
}
