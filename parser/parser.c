/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:54:14 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/06 10:54:32 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe(t_token *token)
{
	if (token->next)
	{
		if (token->next->type == PIPE)
			return (printf("syntax error near unexpected token `|'\n"), 1);
		else
			return (0);
	}
	else
		return (printf("syntax error\n"), 1);
}

int	check_red(t_token *token)
{
	if (token->next)
	{
		if (is_red(token->next->type))
			return (printf("syntax error near unexpected token `>'\n"), 1);
		else if (token->next->type == PIPE)
			return (printf("syntax error near unexpected token `|'\n"), 1);
		else
			return (0);
	}
	else
		return (printf("syntax error near unexpected token `newline'\n"), 1);
}

int	check_logic_operations(t_token *token)
{
	if (token->next)
	{
		if (token->next->type == D_AND)
			return (printf("syntax error near unexpected token `&&'\n"), 1);
		if (token->next->type == DPIPE)
			return (printf("syntax error near unexpected token `||'\n"), 1);
	}
	else
		return (printf("syntax error\n"), 1);
	return (0);
}

void	continue_handling(t_token *token, int i, int j)
{
	char	*str;
	char	*arr;
	int		k;

	str = malloc(ft_strlen(token->cmd[i]));
	if (!str)
		return ;
	k = 0;
	j++;
	while (token->cmd[i][j] && !is_white_space(token->cmd[i][j]) \
		&& ft_isalpha((int)token->cmd[i][j]))
	{
		str[k] = token->cmd[i][j];
		k++;
		j++;
		str[k] = '\0';
	}
	// arr = getenv(str);
	// printf("%s\n",arr);
	// if (arr)
	// {
	// 	// free(token->cmd[i]);
	// 	// token->cmd[i] = arr;
	// 	// free(str);
	// }
	// else
	// 	return ;
}

void	handle_expand(t_token *token)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (token)
	{
		i = 0;
		while (token->cmd[i])
		{
			j = 0;
			while (token->cmd[i][j])
			{
				// if (token->cmd[i][j] == '$')
				// 	continue_handling(token, i, j);
				j++;
			}
			i++;
		}
		token = token->next;
	}
}

int	check_syntax(t_token *token)
{
	// handle_expand(token);
	while (token)
	{
		if (token->type == PIPE)
		{
			if (check_pipe(token))
				return (-1);
		}
		else if (is_red(token->type))
		{
			if (check_red(token))
				return (-1);
		}
		else if (token->type == DPIPE || token->type == D_AND)
		{
			if (check_logic_operations(token))
				return (-1);
		}
		token = token->next;
	}
	return (1);
}
