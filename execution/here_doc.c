/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:22:21 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/23 22:04:04 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	write_in_temp_file(t_tree *root, int fd)
{
	char	*str;

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
		ft_putstr_fd(str, fd);
		free(str);
	}
	free(str);
}

static int	fd_to_here_doc(t_tree *root)
{
	int			fd;
	char		*str;

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
		write_in_temp_file(root, fd);
		str = NULL;
		return (fd);
	}
	return (1);
}

int	handle_here_doc(t_tree *root, t_data *data, t_env **env)
{
	data->j = fd_to_here_doc(root);
	if (data->j == -1)
		return (printf("Error opening file\n"), 1);
	data->j = open("/tmp/temp_file", O_RDONLY | O_EXCL, 0655);
	data->status = execute_cmd(root->right, data->infile_fd, \
		data->outfile_fd, env);
	if (data->status == 1)
		return (1);
	data->status = execute_cmd(root->left, data->j, data->outfile_fd, env);
	if (data->status == 1)
		return (1);
	unlink("temp_file");
	return (0);
}
