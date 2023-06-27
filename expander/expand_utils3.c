/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:32:51 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/27 04:01:37 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	skip_in_q(char *line, int *start, char stop)
{
	*start = *start + 1;
	while (line[*start] && line[*start] != stop)
		*start = *start + 1;
	if (line[*start])
		(*start) = (*start) + 1;
}

void	skip_spaces(char *line, int *start)
{
	while (line[(*start)] && is_white_space(line[(*start)]))
		*start = *start + 1;
}

void	skip_char(char *line, int *start)
{
	while (line[*start] && !is_white_space(line[*start]) \
		&& line[*start] != '\"' && line[*start] != '\'' && \
			!is_operator(line[*start]))
		*start = *start + 1;
	if (line[*start] && line[*start] == '\"')
		skip_in_q(line, start, '\"');
	if (line[*start] && line[*start] == '\'')
		skip_in_q(line, start, '\'');
}

void	skip_until(char *line, int *start)
{
	*start = *start + 2;
	skip_spaces(line, start);
	skip_char(line, start);
}

char	*questio_mark(char *line, int *start)
{
	char	*str;

	str = ft_itoa(g_exit_status);
	line = ft_strreplace_no_q(str, line, "?", *start);
	(*start) += ft_strlen(str) - 1;
	free(str);
	return (line);
}
