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
# include "libft/libft.h"

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
# define EXPAND 14

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
}	t_var;

typedef struct s_token
{
	char			*data;
	char			**cmd;
	int				flag;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_lexer
{
	t_token	*tokens;
	int		n_token;
}	t_lexer;

typedef struct s_tree
{
	t_token			*token;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

//	define functions
void	init_var(t_var **var);
t_token	*init_token(size_t x);
void	get_token(t_lexer *lex, char *line);
char	**get_env(char **env);
void	lex_tokens(t_lexer *lex, char **env);
t_tree	*ast_tokenes(t_lexer *lex);

#endif