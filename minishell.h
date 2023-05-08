/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:19:29 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/12 13:34:29 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "libft/libft.h"
# include "get_next_line.h"

# define CMD 1
# define PIPE 2
# define RED_IN 3
# define DPIPE 4
# define D_RED_IN 5
# define C_PARENTHIS 6
# define O_PARENTHIS 7
# define D_AND 9
# define QOUTES 10
# define RED_OUT 11
# define D_RED_OUT 12
# define FILE 13
# define LIMITER 14
# define EXPAND 15

// enum	e_parse
// {
// 	CMD,
// 	PIPE,
// 	RED_IN,
// 	DPIPE,
// 	D_RED_IN,
// 	C_PARENTHIS,
// 	O_PARENTHIS,
// 	AND,
// 	D_AND,
// 	QOUTES,
// 	RED_OUT,
// 	D_RED_OUT,
// 	EXPAND
// };

enum	e_token
{
	D_PIPE = '|',
	D_BIGGER = '>',
	D_SMALLER = '<',
	D_DQOUTE = '\"',
	D_SQOUTE = '\'',
	D_SPACE = ' ',
	D_OPAR = '(',
	D_CPAR = ')',
	D_GEN = -1,
	FLAG = -1,
};

typedef struct s_var
{
	int		i;
	int		j;
	int		status;
	int		check;
	int		is_stored;
	int		counter;
	int		qoutes_flag;
	int		start;
	int		end;
	int		flag;
}	t_var;

typedef struct s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_rock
{
	char			**cmd;
	int				type;
	int				flag;
	struct s_rock	*next;
	struct s_rock	*prev;
}	t_rock;

typedef struct s_lexer
{
	t_rock	*rock;
	int		n_token;
}	t_lexer;

typedef struct s_tree
{
	t_rock			*token;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

char	**get_env(char **env);

void	init_var(t_var **var);
t_token	*init_token(size_t x);
void	get_token(t_token *token, char *line);
t_rock	*lex_token(t_token *token);
// lexer

int		is_red(int a);
int		is_white_space(char c);

void	get_head1(t_rock **head);

void	del_token(t_rock *tok);

void	expand_tokens(t_token *token);

void	get_head1(t_rock **head);

void	free_2dd(char **str);

t_tree	*ast_tokenes(t_lexer *lex);

void	execute(t_tree *root, char **env);

#endif