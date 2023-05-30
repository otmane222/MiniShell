/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:37:30 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/30 16:41:42 by oaboulgh         ###   ########.fr       */
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
# include <errno.h>
# include <dirent.h>
# include <termios.h>
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
# define LIMITER 14
# define EXPAND 15

# define PIPE_L 16
# define PIPE_R 17

int	g_exit_status;

enum	e_token
{
	D_PIPE = '|',
	DD_AND = '&',
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
	int				flag;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_rock
{
	char			**cmd;
	int				type;
	int				flag;
	int				flag2;
	int				expand;
	int				is_last;
	struct s_rock	*next;
	struct s_rock	*prev;
}	t_rock;

typedef struct s_tree
{
	t_rock			*token;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;


typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

t_env	*put_env_to_new(char **env);
void	add_to_env(char *var, char *val, t_env **env);
t_token	*init_token(size_t x);
char	*expand_line(char *line, t_env *our_env);
int		get_token(t_token **token, char *line);
void	get_head1(t_rock **head);
int		ft_printf(const char *format, ...);

t_rock	*lex_token(t_token **token);
int		check_errors(t_token *token);
void	free_tokens(t_token **token);
t_tree	*ast_tokenes(t_rock *rock);
void	execute(t_tree *root, t_env **env);

#endif