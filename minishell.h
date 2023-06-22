/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:37:30 by nakebli           #+#    #+#             */
/*   Updated: 2023/06/22 03:08:10 by oaboulgh         ###   ########.fr       */
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
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
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
# define PIPE_LR 18
# define PIPE_RL 19

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
	int				*arr;
	int				expand;
	int				red_p;
	int				is_exit;
	int				is_last;
	struct s_rock	*next;
	struct s_rock	*prev;
}	t_rock;

typedef struct s_heredoc
{
	t_rock			*token;
	char			*name;
	int				infile_fd;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_heredoc;

typedef struct s_tree
{
	t_rock			*token;
	t_heredoc		*heredoc;
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
void	remove_from_env(char *var, t_env **env);
void	add_to_env(char *var, char *val, t_env **env);
t_token	*init_token(size_t x);

void	handle_wildcard(t_token **tok);

char	*expand_line(char *line, t_env *our_env);
int		get_token(t_token **token, char *line, t_env *env);
void	get_head1(t_rock **head);
int		ft_printf(const char *format, ...);

t_tree	*tree_head(t_tree *root);

t_rock	*lex_token(t_token **token);
int		check_errors(t_token *token);
void	free_tokens(t_token **token);
void	free_tree(t_tree *tree);
t_tree	*ast_tokenes(t_rock *rock, t_env *env);
void	execute(t_tree *root, t_env **env);
char	*get_next_line(int fd);
void	free_env(t_env **our_env);
void	free_rock(t_rock **rock);

void	signal_handler_call(void);

int		is_there_here_doc(int k);
int		std_in_fd(int k);
int		stop_execution(int k);
int		runnig_cmd(int k);

#endif
