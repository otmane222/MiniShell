/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:35:42 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/17 22:44:28 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_job(char **env)
{
	t_env	*our_env;
	t_token	*token;
	char	*line;
	t_rock	*rock;

	our_env = NULL;
	if (!our_env)
		our_env = put_env_to_new(env);
	line = readline("\x1B[34mMinishell >  \x1B[0m");
	if (line == NULL)
		exit (0);
	line = ft_strtrim(line, " \t\r\v\f");
	add_history(line);
	line = expand_line(line, our_env);
	token = init_token(ft_strlen(line) + 1);
	get_token(token, line);
	free(line);
	rock = lex_token(token);
	while (rock)
	{
		printf("%s -> %d\n", rock->cmd[0], rock->type);
		rock = rock->next;
	}
}

void	lk(void)
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	// atexit(lk);
	while (1)
	{
		(void)ac;
		(void)av;
		start_job(env);
	}
	return (0);
}
