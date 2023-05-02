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

static void	start_job(char **env)
{
	char	*line;
	char	**token;
	t_lexer	*lex;
	t_tree	*root;

	lex = malloc(sizeof(t_lexer));
	line = readline("Minishell >");
	add_history(line);
	if (line == NULL || !ft_strncmp(line, "exit\n", 6))
		exit (0);
	get_token(lex, ft_strtrim(line, " "));
	lex_tokens(lex, env); // put the type of each token in  int type
	root = ast_tokenes(lex);
	execute(root, env);
	free(line);
}

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
/*
	printf("root->left %s\n", root->left->token->cmd[0]);
	printf("root %s\n", root->token->cmd[0]);
	printf("root->right->left %s\n", root->right->left->token->cmd[0]);
	printf("root->right %s\n", root->right->token->cmd[0]);
	printf("root->right->right %s\n", root->right->right->token->cmd[0]);
*/