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

	(void) our_env;
	line = readline("Minishell > ");
	if (line == NULL)
		exit (0);
	line = ft_strtrim(line, " \t\r\v\f\n");
	if (!line[0])
		return (free(line));
	add_history(line);
	token = init_token(ft_strlen(line));
	if (!get_token(&token, line))
		return (free(line));
	free(line);
	rock = lex_token(&token);
	get_head1(&rock);
	tree = ast_tokenes(rock, *our_env);
	execute(tree, our_env);
	free_tree(tree);
}

int	main(int ac, char **av, char **env)
{
	t_env	*our_env;

	g_exit_status = 0;
	our_env = put_env_to_new(env);
	while (1)
	{
		(void)ac;
		(void)av;
		start_job(&our_env);
	}
	free_env(&our_env);
	return (0);
}
