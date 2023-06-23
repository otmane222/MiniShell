/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:36:57 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/22 04:17:41 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	skip_najmat(char *line, int *j)
{
	while (line[(*j)] && line[(*j)] == '*')
		*j = *j + 1;
}

void	skip_q(char *line, int *i, char c)
{
	*i = *i + 1;
	while (line[*i] && line[*i] != c)
		*i = *i + 1;
	if (!line[*i])
		return ;
	*i = *i + 1;
	if (line[*i] && line[*i] == '\'')
		skip_q(line, i, '\'');
	if (line[*i] && line[*i] == '\"')
		skip_q(line, i, '\"');
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

void	make_list(t_token **head, t_token **tmp, t_filename *files, t_var *var)
{
	t_token	*node;

	while (files)
	{
		if (files->usable)
		{
			node = init_token_wild();
			node->data = ft_strdup(files->name);
			if (!var->flag)
			{
				*tmp = node;
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
}

void	add_wildcard_to_list(t_token **tok, t_token **head, \
			t_token *tmp, t_var *var)
{
	t_token	*tmp2;

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
