/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:35:58 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/04 00:04:08 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	is_operator2(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == ')' \
		|| c == '(')
		return (1);
	return (0);
}

int	is_valid(int a)
{
	if (is_white_space(a) || is_operator2(a))
		return (1);
	return (0);
}

char	*chars(char *line, t_var *var)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	k = 0;
	while (!is_not_q(line, &var->start))
		;
	if (!line || line[var->start] == '\0' || is_valid(line[var->start]))
		return (NULL);
	if (line[var->start] == '*')
	{
		while (line[var->start] && line[var->start] == '*')
			var->start++;
		if (!line[var->start] || is_valid(line[var->start]))
		{
			var->i = var->start;
			return (NULL);
		}
	}
	i = var->start;
	while (line[i] && line[i] != '*')
	{
		if (line[i] == '\'')
			skip_q(line, &i, '\'');
		if (line[i] == '\"')
			skip_q(line, &i, '\"');
		if (!line[i])
			break ;
		i++;
	}
	str = malloc(sizeof(char) * i - var->start + 1);
	if (!str)
		return (NULL);
	j = 0;
	i = var->start;
	while (line[i] && line[i] != '*' && \
		!is_valid(line[i]))
	{
		if (line[i] == '\'')
			str = store_datas(str, line, &i, &j, var);
		if (line[i] == '\"')
			str = store_datad(str, line, &i, &j, var);
		if (!line[i] || is_valid(line[var->start]) || line[i] == '*')
			break ;
		str[j] = line[i];
		i++;
		j++;
	}
	if (!line[i] || is_valid(line[var->start]))
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
			node = init_token_wild(ft_strlen(files->name));
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
	while (!is_not_q((*tok)->data, &var->i))
		;
	if ((*tok)->data[var->i] == '*')
		var->check = 0;
	while ((*tok)->data[var->i])
	{
		if (is_valid((*tok)->data[var->i]))
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

void	wild_card_handle(t_token **token)
{
	t_token	*tmp;

	while ((*token))
	{
		handle_wildcard(token);
		if (!(*token))
			break ;
		tmp = (*token);
		(*token) = (*token)->next;
	}
	while (tmp->prev)
		tmp = tmp->prev;
	(*token) = tmp;
}
