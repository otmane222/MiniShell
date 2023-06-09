/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:21:19 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/09 23:29:53 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

char	*store_datass(char *str, char *line, int *i, int *j)
{
	*i = *i + 1;
	str[*j] = line[*i];
	*i = *i + 1;
	*j = *j + 1;
	while (line[*i] && line[*i] != '\'')
	{
		str[*j] = line[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
	str[*j] = line[*i];
	*i = *i + 1;
	*j = *j + 1;
	str[*j] = '\0';
	if (line[*i] == '\"')
		str = store_datadd(str, line, i, j);
	if (line[*i] == '\'')
		str = store_datass(str, line, i, j);
	return (str);
}

char	*store_datadd(char *str, char *line, int *i, int *j)
{
	*i = *i + 1;
	str[*j] = line[*i];
	*i = *i + 1;
	*j = *j + 1;
	while (line[*i] && line[*i] != '\"')
	{
		str[*j] = line[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
	str[*j] = line[*i];
	*i = *i + 1;
	*j = *j + 1;
	str[*j] = '\0';
	if (line[*i] == '\'')
		str = store_datass(str, line, i, j);
	if (line[*i] == '\"')
		str = store_datadd(str, line, i, j);
	return (str);
}

static char	*handle_case(char *line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * ft_strlen(line));
	if (!str)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] == '\'')
			str = store_datass(str, line, &i, &j);
		if (line[i] == '$' && line[i + 1] && line[i + 1] == '\"')
			str = store_datadd(str, line, &i, &j);
		if (!line[i])
			break ;
		if (line[i] == '$')
			continue ;
		str[j] = line[i];
		j++;
		i++;
	}
	str[j] = '\0';
	free(line);
	return (str);
}

t_tree	*call_ninja(t_tree *tree, t_rock *rock, t_env *env)
{
	char		*str1;
	char		*str;
	char		*tmp;
	static int	i = 0;
	int			fd;

	i++;
	fd = 0;
	tree->heredoc = malloc(sizeof(t_heredoc));
	if (!tree->heredoc)
		return (NULL);
	tree->heredoc->token = rock;
	tree->heredoc->left = NULL;
	tree->heredoc->right = NULL;
	str1 = ft_itoa(i);
	tmp = str1;
	str1 = ft_strjoin("/tmp/temp_file", str1);
	free(tmp);
	fd = open(str1, O_RDWR | O_CREAT | O_TRUNC, 0655);
	if (fd == -1)
		printf ("Error opening :%s\n", str1);
	tree->heredoc->token->next->cmd[0] = handle_case(tree->heredoc->token->next->cmd[0]);
	tree->heredoc->token->next->cmd[0] = deleted_q(tree->heredoc->token->next->cmd[0]);
	while (1)
	{
		write(1, "> ", 3);
		str = get_next_line(STDIN_FILENO);
		if (str == NULL)
			break ;
		if (ft_strncmp(str, tree->heredoc->token->next->cmd[0], \
			ft_strlen(str) - 1) == 0 && \
			ft_strlen(str) - 1 == ft_strlen(tree->heredoc->token->next->cmd[0]))
			break ;
		if (tree->heredoc->token->expand)
			str = expand_line(str, env);
		ft_putstr_fd(str, fd);
		free(str);
		str = NULL;
	}
	free(str);
	tree->heredoc->name = str1;
	tree->heredoc->infile_fd = fd;
	close(fd);
	tree->heredoc->left = ast_redirections(rock->prev, RED_OUT, env);
	tree->heredoc->right = ast_redirections(rock->next, RED_OUT, env);
	return (tree);
}

static t_tree	*fill_right_left(t_tree *tree, t_rock *rock, int flag, t_env *env)
{
	if (flag == 1)
		rock->red_p = 1;
	rock->flag = 0;
	if (rock->type == D_RED_IN)
		return (call_ninja(tree, rock, env));
	tree->token = rock;
	tree->left = ast_redirections(rock->prev, flag, env);
	tree->right = ast_redirections(rock->next, flag, env);
	return (tree);
}

t_rock	*get_last(t_rock *rock)
{
	if (!rock)
		return (NULL);
	if (!rock->next)
		return (rock);
	while (rock->next && rock->next->flag)
		rock = rock->next;
	return (rock);
}

static t_tree	*case_file(t_rock *tmp, t_tree *tree, t_env *env)
{
	t_rock	*tmp2;
	t_rock	*tmp3;

	tmp3 = get_last(tmp);
	if (tmp->type == O_PARENTHIS)
	{
		tmp2 = tmp->next;
		tmp2->is_exit = 1;
		del_token(tmp);
		del_token(tmp3);
		free(tree);
		return (ast_and(tmp2, env));
	}
	else
	{
		tree->token = tmp;
		tree->token->flag = 0;
		return (tree);
	}
}

int	is_red(int a)
{
	if (a == D_RED_OUT || a == RED_IN || a == RED_OUT || a == D_RED_IN)
		return (1);
	return (0);
}

void	get_tail(t_rock **head)
{
	if (!(*head) || !(*head)->flag)
		return ;
	if (!(*head)->next || !(*head)->next->flag)
		return ;
	while ((*head)->next)
	{
		if ((*head)->next->flag == 0)
			break ;
		(*head) = (*head)->next;
	}
}

void	skip_parenthese1(t_rock **rock)
{
	int	i;

	i = 0;
	if ((*rock)->type == C_PARENTHIS)
	{
		while ((*rock) && (*rock)->flag)
		{
			if ((*rock)->type == C_PARENTHIS)
				i++;
			else if ((*rock)->type == O_PARENTHIS)
			{
				i--;
				if (i == 0)
					break ;
			}
			*rock = (*rock)->prev;
		}
	}
}

t_tree	*ast_redirections(t_rock *rock, int flag, t_env *env)
{
	t_var	var;
	t_rock	*tmp;
	t_tree	*tree;

	if (!rock || !rock->flag)
		return (NULL);
	tree = init_tree();
	get_head(&rock);
	tmp = rock;
	var.i = 0;
	flag = 0;
	while (rock && rock->flag)
	{
		skip_parenthese(&rock);
		if (is_red(rock->type))
		{
			if (rock->prev && rock->prev->type == C_PARENTHIS)
				flag = 1;
			var.i = 1;
			break ;
		}
		rock = rock->next;
	}
	if (var.i == 0)
		return (case_file(tmp, tree, env));
	else if (var.i)
		return (fill_right_left(tree, rock, flag, env));
	return (NULL);
}
