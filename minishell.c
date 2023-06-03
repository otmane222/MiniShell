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

void	print_tree(t_tree *tree)
{
	int			i;
	static int	j = 0;

	i = 0;
	if (!tree)
		return ;
	while (tree->token->cmd[i])
	{
		printf("%s	", tree->token->cmd[i]);
		i++;
	}
	printf("\n-----%d------\n", j++);
	print_tree(tree->left);
	print_tree(tree->right);
}

void	free_rock(t_rock **rock)
{
	t_rock	*tmp;

	while ((*rock))
	{
		tmp = (*rock);
		(*rock) = (*rock)->next;
		free_2dd(tmp->cmd);
		free(tmp);
		tmp = NULL;
	}
}

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	if (tree->token)
	{
		free_2dd(tree->token->cmd);
		free(tree->token);
	}
	free(tree);
	tree = NULL;
}

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

	// (void) our_env;
	line = readline("\x1B[34mMinishell >  \x1B[0m");
	if (line == NULL)
		exit (0);
	line = ft_strtrim(line, " \t\r\v\f\n");
	if (!line[0])
		return ;
	add_history(line);
	// line = expand_line(line, *our_env);
	token = init_token(ft_strlen(line));
	if (!get_token(&token, line))
		return (free(line));
	free(line);
	rock = lex_token(&token);
	get_head1(&rock);
	tree = ast_tokenes(rock);
	tree_head(tree);
	execute(tree, our_env);
	// print_tree(tree);
	free_tree(tree);
}

void	lk(void)
{
	system("leaks minishell");
}

void	free_env(t_env **our_env)
{
	t_env	*tmp;

	while ((*our_env))
	{
		tmp = (*our_env);
		(*our_env) = (*our_env)->next;
		free(tmp->value);
		free(tmp->key);
		free(tmp);
		tmp = NULL;
	}
}

void	disableInputBuffering(void)
{
	struct termios	term;

	tcgetattr (STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &term);
}

int	main(int ac, char **av, char **env)
{
	t_env	*our_env;

	// atexit(lk);
	// disableInputBuffering();
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
