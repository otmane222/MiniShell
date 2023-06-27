/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:37:05 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/25 17:27:54 by oaboulgh         ###   ########.fr       */
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

static void	full_files(t_filename **files, struct dirent *entity, int flag)
{
	if (!flag)
	{
		if (entity->d_name[0] == '.')
			return ;
	}
	(*files)->next = init_t_file();
	(*files)->next->name = ft_strdup(entity->d_name);
	(*files) = (*files)->next;
}

static void	first_attemp(t_filename **files, struct dirent *entity, \
	t_filename **head, int flag)
{
	if (!flag)
	{
		if (entity->d_name[0] == '.')
			return ;
	}
	(*files) = init_t_file();
	*head = *files;
	(*files)->name = ft_strdup(entity->d_name);
}

void	skip_dots(int *flag, struct dirent **entity, DIR **dir)
{
	*flag = 0;
	while ((*entity) && (*entity)->d_name[0] == '.')
		(*entity) = readdir(*dir);
}

t_filename	*get_files_name(char *line, int *flag)
{
	DIR				*dir;
	struct dirent	*entity;
	t_filename		*files;
	t_filename		*head;

	files = NULL;
	head = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	entity = readdir(dir);
	if (line[0] != '.')
		skip_dots(flag, &entity, &dir);
	if (entity)
		first_attemp(&files, entity, &head, *flag);
	while (entity)
	{
		entity = readdir(dir);
		if (entity)
			full_files(&files, entity, *flag);
	}
	return (closedir(dir), head);
}
