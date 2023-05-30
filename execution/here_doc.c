/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:22:21 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/30 15:36:29 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// static int	write_in_temp_file(t_tree *root)
// {
// 	char	*str;
// 	int		fd;

// 	fd = open("/tmp/temp_file", O_RDWR | O_CREAT | O_TRUNC, 0655);
// 	if (fd == -1)
// 	{
// 		printf ("Error opening :%s\n", "/tmp/temp_file");
// 		return (-1);
// 	}
// 	while (1)
// 	{
// 		write(1, "> ", 3);
// 		str = get_next_line(0);
// 		if (str == NULL)
// 			break ;
// 		if (ft_strncmp(str, root->token->next->cmd[0], \
// 			ft_strlen(str) - 1) == 0 && \
// 			ft_strlen(str) - 1 == ft_strlen(root->token->next->cmd[0]))
// 			break ;
// 		ft_putstr_fd(str, fd);
// 		free(str);
// 		str = NULL;
// 	}
// 	free(str);
// 	close(fd);
// 	return (fd);
// }

// static int	fd_to_here_doc(t_tree *root)
// {
// 	int			fd;

// 	fd = write_in_temp_file(root);
// 	return (fd);
// }

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

int	handle_here_doc(t_tree *root, t_data data, t_env **env, t_fds *list)
{
	int	k;

	data.j = fd_to_here_doc(root, *env);
	if (data.j == 1)
		return (1);
	data.j = open("/tmp/temp_file", O_RDONLY | O_EXCL, 0655);
	if (data.j == 1)
		return (1);
	add_b_list(&list, init_list(data.j));
	k = data.infile_fd;
	data.infile_fd = data.j;
	if (execute_cmd(root->left, data, env, list))
		return (1);
	data.infile_fd = k;
	if (execute_cmd(root->right, data, env, list))
		return (1);
	unlink("/tmp/temp_file");
	return (0);
}
