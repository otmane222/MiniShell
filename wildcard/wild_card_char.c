/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:32:33 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/25 17:19:16 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char	*change_line(char *line, t_filename *files, t_var *var)
{
	int	i;

	i = var->j;
	while (line[i] && line[i] != ' ')
		i++;
	i = i - var->j;
	while (files)
	{
		if (files->usable == 1)
		{
			line = ft_strreplace1(files->name, line, i, var->j);
			var->i += ft_strlen(files->name) - i;
			var->j += ft_strlen(files->name);
			i = 0;
		}
		files = files->next;
	}
	var->i += i;
	return (line);
}

char	*wild_card_line_char(char *line, t_var *var, t_filename *files)
{
	char		**to_find;
	int			k;
	t_filename	*tmp;

	var->flag = 0;
	k = 0;
	tmp = NULL;
	to_find = to_find_str(line, var);
	search_for_same_files(to_find, files, var);
	tmp = files;
	free_2dd(to_find);
	while (files)
	{
		if (files->usable)
			k++;
		files = files->next;
	}
	files = tmp;
	if (k >= 2)
		return (NULL);
	line = change_line(line, files, var);
	return (line);
}

static char	*get_wildcard_line(t_var *var, char *line, t_filename *files)
{
	while (line[var->i])
	{
		if (is_valid(line[var->i]))
		{
			var->j = var->i + 1;
			if (line[var->j] == '*')
				var->check = 0;
			var->start = var->i + 1;
		}
		if (line[var->i] == '*')
		{
			line = wild_card_line_char(line, var, files);
			break ;
		}
		var->i++;
	}
	return (line);
}

char	*handle_wildcard_char(char *line)
{
	t_var		*var;
	t_filename	*files;
	int			flag;

	flag = 1;
	if (!line)
		return (NULL);
	files = get_files_name(line, &flag);
	init_var_2(&var);
	while (!is_not_q(line, &var->i))
		;
	if (line[var->i] == '*')
		var->check = 0;
	line = get_wildcard_line(var, line, files);
	free_all3(var, files);
	return (line);
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
