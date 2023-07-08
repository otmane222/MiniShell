/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:35:42 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/22 15:10:33 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

t_tree	*tree_head(t_tree *root)
{
	static t_tree	*tree;

	if (!tree)
		return (tree);
	else
		tree = root;
	return (NULL);
}

void	call_exit(void)
{
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	exit (g_exit_status);
}

char	*read_line(void)
{
	char	*input;
	char	*line;

	if (isatty(STDIN_FILENO))
		input = readline("Minishell > ");
	else
		input = get_next_line(STDIN_FILENO);
	line = ft_strtrim(input, " \t\r\v\f\n");
	return (line);
}

static void	start_job(t_env **our_env)
{
	t_token	*token;
	t_rock	*rock;
	t_tree	*tree;
	char	*line;

	token = NULL;
	line = read_line();
	if (line == NULL)
		call_exit();
	if (!line[0])
		return (free(line));
	add_history(line);
	if (!get_token(&token, line, *our_env))
		return (free_tokens(&token));
	rock = lex_token(&token);
	get_head1(&rock);
	tree = ast_tokenes(rock, *our_env);
	if (stop_execution(-1) == -2)
		return (stop_execution(0), free_tree(tree));
	execute(tree, our_env);
	free_tree(tree);
}

int	main(int ac, char **av, char **env)
{
	t_env	*our_env;

	g_exit_status = 0;
	our_env = put_env_to_new(env);
	handle_shell_lvl(&our_env);
	signal_handler_call();
	std_in_fd(-2);
	while (1)
	{
		get_std_in();
		(void)ac;
		(void)av;
		start_job(&our_env);
	}
	free_env(&our_env);
	return (0);
}
