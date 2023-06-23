/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:19:53 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/22 23:13:49 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*handle_tild(char *line, t_env *our_env)
{
	char	*new_line;

	new_line = ft_strjoin(ft_getenv("HOME", our_env), &line[1]);
	free(line);
	return (new_line);
}

char	*expand_line(char *line, t_env *our_env)
{
	if (line[0] == '~' && (line[1] == '/' || !line[1]))
	{
		line = handle_tild(line, our_env);
		return (line);
	}
	line = continue_expand(line, our_env);
	return (line);
}
