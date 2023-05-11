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
	t_token		*token;
	t_lexer		*lex;
	t_tree		*root;
	char		*line;
	t_env		*our_env;

	our_env = put_env_to_new(env);
	lex = malloc(sizeof(t_lexer));
	token = init_token(ft_strlen(line) + 1);
	line = readline("\x1B[34mMinishell >  \x1B[0m");
	add_history(line);
	if (line == NULL)
		exit (0);
	line = ft_strtrim(line, " ");
	line = expand_line(line, our_env);
	get_token(token, line);
	lex->rock = lex_token(token);
	get_head1(&lex->rock);

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
	
	int	i = 0;
	while (lex->rock)
	{
		i = 0;
		while (lex->rock->cmd[i])
			printf("%s\t", lex->rock->cmd[i++]);
		printf("\n");
		lex->rock = lex->rock->next;
	}
}
	// free(lex);

	// i = check_syntax(lex->tokens);
	// if (i == -1)
	// {
	// 	return ;
	// 	free_tokens(lex->tokens);
	// }

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
