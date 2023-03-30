/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:19:19 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/03/30 14:17:41 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_job(void)
{
	char	*line;
	char	**token;
	t_lexer	*lex;

	lex = malloc(sizeof(t_lexer));
	line = readline("Minishell > ");
	if (line == NULL)
	{
		printf("Error: unable to read line\n");
		return ;
	}
	get_token(lex, ft_strtrim(line, " "));
	free(line);
}

int	main(int ac, char **av)
{
	while (1)
	{
		start_job();
	}
	return (0);
}
