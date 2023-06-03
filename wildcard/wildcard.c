/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:35:58 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/03 16:54:47 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char	*chars(char *line, t_var *var)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	k = 0;
	if (!line || line[var->start] == '\0' || line[var->start] == ' ')
		return (NULL);
	if (line[var->start] == '*')
	{
		while (line[var->start] && line[var->start] == '*')
			var->start++;
		if (!line[var->start] || line[var->start] == ' ')
		{
			var->i = var->start;
			return (NULL);
		}
	}
	i = var->start;
	while (line[i] && line[i] != '*')
		i++;
	str = malloc(sizeof(char) * i - var->start + 1);
	if (!str)
		return (NULL);
	j = 0;
	i = var->start;
	while (line[i] && line[i] != '*' && \
		line[i] != ' ')
	{
		if (line[i] == '\'')
		{
			var->start += 2;
			str = store_datas(str, line, &i, &j);
		}
		if (!line[i] || line[i] == ' ')
			break ;
		str[j] = line[i];
		i++;
		j++;
	}
	if (!line[i] || line[i] == ' ')
		var->end = 1;
	str[j] = '\0';
	var->start += ft_strlen(str);
	return (str);
}

char	**to_find_str(char *line, t_var *var)
{
	char	**find;
	int		num_to_search;
	int		i;

	i = 0;
	num_to_search = num_of_char(&line[var->start]);
	find = malloc(sizeof(char *) * num_to_search);
	if (!find)
		return (NULL);
	while (i < num_to_search)
	{
		find[i] = chars(line, var);
		i++;
	}
	find[num_to_search - 1] = NULL;
	return (find);
}

char	*change_line(char *line, t_filename *files, t_var *var)
{
	int	i;
	int	j;

	j = 0;
	i = var->j;
	while (line[i] && line[i] != ' ')
		i++;
	i = i - var->j;
	while (files)
	{
		if (files->usable == 1)
		{
			line = ft_strreplace1(files->name, line, i, var->j);
			var->i += ft_strlen(files->name) + 1 - i;
			var->j += ft_strlen(files->name) + 1;
			i = 0;
		}
		files = files->next;
	}
	var->i += i;
	return (line);
}

void	wild_card_line(t_token **tok, t_var *var, t_filename *files, t_token **head)
{
	char		**to_find;
	t_token		*node;
	t_token		*tmp;
	t_token		*tmp1;
	t_token		*tmp2;

	var->flag = 0;
	tmp1 = NULL;
	to_find = to_find_str((*tok)->data, var);
	search_for_same_files(to_find, files, var);
	while (files)
	{
		if (files->usable)
		{
			node = init_token(ft_strlen(files->name));
			node->data = ft_strdup(files->name);
			if (!var->flag)
			{
				tmp = node;
				var->flag = 1;
			}
			if (!*head)
				*head = node;
			else
			{
				(*head)->next = node;
				node->prev = *head;
				(*head) = (*head)->next;
			}
		}
		files = files->next;
	}
	free_2dd(to_find);
	if (var->flag && (*tok)->next)
	{
		(*tok)->next->prev = *head;
		(*head)->next = (*tok)->next;
	}
	if (var->flag && (*tok)->prev)
	{
		(*tok)->prev->next = tmp;
		tmp->prev = (*tok)->prev;
	}
	if (var->flag && !(*tok)->next && !(*tok)->prev)
	{
		tmp2 = (*tok);
		(*tok) = (*head);
		free(tmp2->data);
		free(tmp2);
		tmp2 = NULL;
	}
	else if (var->flag)
	{
		tmp2 = (*tok);
		(*tok) = (*head);
		free(tmp2->data);
		free(tmp2);
		tmp2 = NULL;
	}
}

void	free_all3(t_var *var, t_filename *files)
{
	t_filename	*tmp;

	free(var);
	while (files)
	{
		tmp = files;
		files = files->next;
		free(tmp->name);
		free(tmp);
	}
}

void	handle_wildcard(t_token **tok)
{
	t_token		*head;
	t_var		*var;
	t_filename	*files;

	head = NULL;
	if (!tok || !(*tok) || !(*tok)->data)
		return ;
	files = get_files_name();
	init_var_2(&var);
	if ((*tok)->data[0] == '*')
		var->check = 0;
	while ((*tok)->data[var->i])
	{
		if ((*tok)->data[var->i] == ' ')
		{
			var->j = var->i + 1;
			if ((*tok)->data[var->j] == '*')
				var->check = 0;
			var->start = var->i + 1;
		}
		if ((*tok)->data[var->i] == '*')
		{
			wild_card_line(tok, var, files, &head);
			break ;
		}
		var->i++;
	}
	free_all3(var, files);
}
