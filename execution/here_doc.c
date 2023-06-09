/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:22:21 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/08 18:08:42 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	fd_to_here_doc(t_tree *root, t_env *env)
{
	int			fd;
	char		*str;

	(void)env;
	root = root->right;
	while (root->left)
		root = root->left;
	if (root->token->type == LIMITER)
	{
		root->token->cmd[0] = deleted_q(root->token->cmd[0]);
		fd = open("/tmp/temp_file", O_RDWR | O_CREAT | O_TRUNC, 0655);
		if (fd == -1)
		{
			printf ("Error opening :%s\n", "/tmp/temp_file");
			return (1);
		}
		while (1)
		{
			write(1, "> ", 3);
			str = get_next_line(STDIN_FILENO);
			if (str == NULL)
				break ;
			if (ft_strncmp(str, root->token->cmd[0], \
				ft_strlen(str) - 1) == 0 && \
				ft_strlen(str) - 1 == ft_strlen(root->token->cmd[0]))
				break ;
			if (root->token->expand)
				str = expand_line(str, env);
			ft_putstr_fd(str, fd);
			free(str);
		}
		close(fd);
		free(str);
		str = NULL;
		return (fd);
	}
	return (1);
}

int	handle_here_doc(t_tree *root, t_data data, t_env **env, t_fds **list)
{
	int	k;

	if (root->heredoc->infile_fd == -1)
		return (1);
	data.j = open(root->heredoc->name, O_RDONLY | O_EXCL, 0655);
	if (data.j == -1)
		return (1);
	add_b_list(list, init_list(data.j));
	k = data.infile_fd;
	if (!data.redin)
		data.infile_fd = data.j;
	data.redin = D_RED_IN;
	if (execute_cmd(root->heredoc->left, data, env, list))
		return (close(data.j), 1);
	// data.infile_fd = k;
	// if (execute_cmd(root->heredoc->right, data, env, list))
	// 	return (close(data.j), 1);
	close(data.j);
	unlink(root->heredoc->name);
	return (0);
}
