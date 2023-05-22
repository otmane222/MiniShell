<<<<<<< HEAD
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

static void	start_job(t_env **our_env)
{
	t_token	*token;
	t_rock	*rock;
	// t_tree	*tree;
	char	*line;

	line = readline("\x1B[34mMinishell >  \x1B[0m");
	if (line == NULL)
		exit (0);
	line = ft_strtrim(line, " \t\r\v\f");
	add_history(line);
	line = expand_line(line, *our_env);
	token = init_token(ft_strlen(line) + 1);
	if (!get_token(&token, line))
		return (free(line));
	free(line);
	rock = lex_token(&token);
	free_rock(&rock);
	
	// tree = ast_tokenes(rock);
	// print_tree(tree);
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

int	main(int ac, char **av, char **env)
{
	t_env	*our_env;

	atexit(lk);
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
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:19:19 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/12 14:19:00 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_in_cmd/builtin.h"

void	free_tree(t_tree *tree)
{
	t_tree	*tmp;
	t_tree	*tmp1;

	if (!tree)
		return ;
	tmp = tree;
	free_tree(tree->left);
	free_tree(tree->right);
	free(tmp);
}

void	free_rocks(t_lexer *lex)
{
	t_rock	*tmp;

	while (lex->rock)
	{
		tmp = lex->rock;
		lex->rock = lex->rock->next;
		free_2dd(tmp->cmd);
		free(tmp);
	}
	free(lex);
}

static void	start_job(char **env)
{
	t_token			*token;
	t_lexer			*lex;
	t_tree			*root;
	char			*line;
	static t_env	*our_env;

	if (!our_env)
		our_env = put_env_to_new(env);
	lex = malloc(sizeof(t_lexer));
	line = readline("\x1B[34mMinishell >  \x1B[0m");
	token = init_token(ft_strlen(line) + 1);
	add_history(line);
	if (line == NULL)
		exit (0);
	line = ft_strtrim(line, " ");
	line = expand_line(line, our_env);
	get_token(token, line);
	lex->rock = lex_token(token);
	get_head1(&lex->rock);
	int i = check_syntax(lex->rock);
	if (i == -1)
	{
		return ;
		// free_tokens(lex->tokens);
	}
	builtin_cmds(&lex->rock, &our_env);
	
	
	
	
	// root = ast_tokenes(lex);

	// printf("%s\n", root->token->cmd[0]);
	// printf("%s\n", root->right->token->cmd[0]);
	// execute(root, env);

	// free_rocks(lex);
	// free_tree(root);
	// free(line);

	// exit(0);
	// while (token)
	// {
	// 	printf("%s\n", token->data);
	// 	token = token->next;
	// }
	
	// int	i = 0;
	// while (lex->rock)
	// {
	// 	i = 0;
	// 	while (lex->rock->cmd[i])
	// 		printf("%s\t", lex->rock->cmd[i++]);
	// 	printf("\n");
	// 	lex->rock = lex->rock->next;
	// }
}
	// free(lex);


void	lk(void)
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	while (1)
	{
		start_job(env);
	}
	return (0);
}
>>>>>>> 5b403648007d759a46feb40e78a8dc3ec22f6161
