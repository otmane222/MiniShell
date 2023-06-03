/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:29:48 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/03 13:33:51 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

// int	there_is(char *to_find, char *str, t_var *var)
// {
// 	int		i;

// 	i = 0;
// 	if (ft_strlen(str) < var->i)
// 		return (0);
// 	else if (ft_strfind(str, to_find, ft_strlen(str), var->end - var->start))
// 		return (1);
// 	return (0);
// }

void	inti_var_to_0(t_var *var)
{
	var->i = 0;
	var->j = 0;
	var->counter = 0;
	var->flag = 0;
}

void	skip_q(char *line, int *i, char c)
{
	*i = *i + 1;
	while (line[*i] && line[*i] != c)
		*i = *i + 1;
	if (line[*i] && line[*i] == '\'')
		skip_q(line, i, '\'');
	if (line[*i] && line[*i] == '\"')
		skip_q(line, i, '\"');
}

void	search_for_same_files(char **to_find, t_filename *files, t_var *var)
{
	int			i;
	int			counter;
	t_filename	*tmp;

	i = 0;
	tmp = files;
	counter = 0;
	while (to_find[i])
	{
		files = tmp;
		while (files)
		{
			if (ft_strlen(files->name) >= ft_strlen(to_find[i]) \
				&& (int)ft_strlen(files->name) >= files->counter)
			{
				counter = found_it(&files->name[files->counter], \
					to_find[i], ft_strlen(files->name));
				if (!counter)
					files->usable = 0;
				else if (i == 0 && var->check && ft_strncmp(files->name, \
					to_find[0], ft_strlen(to_find[0])))
					files->usable = 0;
				else if (!to_find[i + 1] && var->end && ft_strncmp(&files-> name[ft_strlen(files->name) - ft_strlen(to_find[i])], to_find[i], ft_strlen(to_find[i])))
					files->usable = 0;
				else
					files->counter = counter;
			}
			else
				files->usable = 0;
			files = files->next;
		}
		i++;
	}
}

char	*store_datas(char *str, char *line, int *i, int *j)
{
	*i = *i + 1;
	while (line[*i] && line[*i] != '\'')
	{
		str[*j] = line[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
	str[*j] = '\0';
	*i = *i + 1;
	return (str);
}
