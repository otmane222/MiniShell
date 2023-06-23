/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:29:48 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/22 21:10:03 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	inti_var_to_0(t_var *var)
{
	var->i = 0;
	var->j = 0;
	var->counter = 0;
	var->flag = 0;
}

static void	compare(int *counter, t_filename *files, t_var *var, char **to_find)
{
	*counter = found_it(&files->name[files->counter], \
	to_find[var->counter], ft_strlen(files->name));
	if (!*counter)
		files->usable = 0;
	else if (var->counter == 0 && var->check && ft_strncmp(files->name, \
		to_find[0], ft_strlen(to_find[0])))
		files->usable = 0;
	else if (!to_find[var->counter + 1] && var->end && \
		ft_strncmp(&files->name[ft_strlen(files->name) - \
		ft_strlen(to_find[var->counter])], to_find[var->counter], \
			ft_strlen(to_find[var->counter])))
		files->usable = 0;
	else
		files->counter = *counter;
}

void	search_for_same_files(char **to_find, t_filename *files, t_var *var)
{
	int			counter;
	t_filename	*tmp;

	tmp = files;
	var->counter = 0;
	counter = 0;
	while (to_find[var->counter])
	{
		files = tmp;
		while (files)
		{
			if (ft_strlen(files->name) >= ft_strlen(to_find[var->counter]) \
				&& (int)ft_strlen(files->name) >= files->counter)
				compare(&counter, files, var, to_find);
			else
				files->usable = 0;
			files = files->next;
		}
		var->counter++;
	}
}

char	*store_datas(char *str, char *line, t_var *va, t_var *var)
{
	var->start += 2;
	va->i = va->i + 1;
	while (line[va->i] && line[va->i] != '\'')
	{
		str[va->j] = line[va->i];
		va->i = va->i + 1;
		va->j = va->j + 1;
	}
	str[va->j] = '\0';
	if (!line[va->i])
		return (str);
	va->i = va->i + 1;
	if (line[va->i] == '\"')
		str = store_datad(str, line, va, var);
	if (line[va->i] == '\'')
		str = store_datas(str, line, va, var);
	return (str);
}

char	*store_datad(char *str, char *line, t_var *va, t_var *var)
{
	var->start += 2;
	va->i = va->i + 1;
	while (line[va->i] && line[va->i] != '\"')
	{
		str[va->j] = line[va->i];
		va->i = va->i + 1;
		va->j = va->j + 1;
	}
	str[va->j] = '\0';
	if (!line[va->i])
		return (str);
	va->i = va->i + 1;
	if (line[va->i] == '\'')
		str = store_datas(str, line, va, var);
	if (line[va->i] == '\"')
		str = store_datad(str, line, va, var);
	return (str);
}
