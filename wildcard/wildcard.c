/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:35:58 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/09 16:38:50 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

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

void	wild_card_line(t_token **tok, t_var *var, \
			t_filename *files, t_token **head)
{
	char		**to_find;
	t_token		*tmp;

	var->flag = 0;
	to_find = to_find_str((*tok)->data, var);
	search_for_same_files(to_find, files, var);
	make_list(head, &tmp, files, var);
	free_2dd(to_find);
	if (var->flag && (*tok)->next)
	{
		(*tok)->next->prev = *head;
		(*head)->next = (*tok)->next;
	}
	add_wildcard_to_list(tok, head, tmp, var);
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
		check_first_char(*tok, var);
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
		if ((*token)->type != FILE && (*token)->type != LIMITER)
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
