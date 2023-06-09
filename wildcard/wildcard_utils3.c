/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:37:05 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/09 16:53:48 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

t_filename	*init_t_file(void)
{
	t_filename	*file;

	file = malloc(sizeof(t_filename));
	if (!file)
		return (NULL);
	file->name = NULL;
	file->counter = 0;
	file->next = NULL;
	file->usable = 1;
	return (file);
}

void	del_tokenx(t_token **tok)
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!tok || !(*tok))
		return ;
	tmp = (*tok)->next;
	tmp2 = (*tok)->prev;
	free((*tok)->data);
	free((*tok));
	(*tok) = NULL;
	if (tmp)
		tmp->prev = tmp2;
	if (tmp2)
		tmp2->next = tmp;
}

t_token	*init_token_wild(void)
{
	t_token	*token;

	token = malloc (sizeof(t_token));
	if (!token)
		return (NULL);
	token->data = NULL;
	token->next = NULL;
	token->flag = -9;
	token->type = -10;
	token->prev = NULL;
	return (token);
}

t_filename	*get_files_name(void)
{
	DIR				*dir;
	struct dirent	*entity;
	t_filename		*files;
	t_filename		*head;

	files = init_t_file();
	head = files;
	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	entity = readdir(dir);
	while (entity && entity->d_name[0] == '.')
		entity = readdir(dir);
	if (entity)
		files->name = ft_strdup(entity->d_name);
	while (entity)
	{
		entity = readdir(dir);
		if (entity && entity->d_name[0] != '.')
		{
			files->next = init_t_file();
			files->next->name = ft_strdup(entity->d_name);
			files = files->next;
		}
	}
	closedir(dir);
	return (head);
}

char	*ft_strfind(const char *big, const char *little, size_t len, int stp)
{
	size_t	i;
	int		j;
	char	*pt;

	i = 0;
	pt = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (len && big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			pt = (char *)big + i;
			j = 0;
			while (big[i + j] == little[j] && i + j < len)
			{
				if (!little[j + 1] || stp <= j)
					return (pt);
				j++;
			}
			pt = 0;
		}
		i++;
	}
	return (NULL);
}
