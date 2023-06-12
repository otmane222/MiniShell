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

static void	start_job(t_env **our_env)
{
	t_token	*token;
	t_rock	*rock;
	t_tree	*tree;
	char	*line;
	char	*input;

	(void) our_env;
	if (isatty(STDIN_FILENO))
		input = readline("Minishell > ");
	else
		input = get_next_line(STDIN_FILENO);
	line = ft_strtrim(input, " \t\r\v\f\n");
	if (line == NULL)
	{
		printf("exit\n");
		exit (g_exit_status);
	}
	if (!line[0])
		return (free(line));
	add_history(line);
	token = init_token(ft_strlen(line));
	if (!get_token(&token, line, *our_env))
		return ;
	rock = lex_token(&token);
	get_head1(&rock);
	tree = ast_tokenes(rock, *our_env);
	execute(tree, our_env);
	free_tree(tree);
}

void	get_std_in(void)
{
	if (!isatty(STDIN_FILENO) && std_in_fd(-1) != -2)
	{
		dup2(std_in_fd(-1), STDIN_FILENO);
		close(std_in_fd(-1));
		std_in_fd(-2);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*our_env;

	g_exit_status = 0;
	our_env = put_env_to_new(env);
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
