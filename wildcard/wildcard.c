/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:35:58 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/01 21:08:07 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	init_var_2(t_var **var)
{
	(*var) = malloc(sizeof(t_var));
	(*var)->i = 0;
	(*var)->j = 0;
	(*var)->check = 1;
	(*var)->status = 0;
	(*var)->counter = 0;
	(*var)->qoutes_flag = 0;
	(*var)->start = 0;
	(*var)->end = 0;
}


static t_filename	*init_t_file(void)
{
	t_filename	*file;

	file = malloc(sizeof(t_filename));
	if (!file)
		return (NULL);
	file->name = NULL;
	file->counter = 0;
	file->next = NULL;
	file->usable = 1;
	return (file);
}

t_filename	*get_files_name(void)
{
	DIR				*dir;
	struct dirent	*entity;
	t_filename		*files;
	t_filename		*head;

	files = init_t_file();
	head = files;
	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	entity = readdir(dir);
	files->name = ft_strdup(entity->d_name);
	while (entity)
	{
		entity = readdir(dir);
		if (entity)
		{
			files->next = init_t_file();
			files->next->name = ft_strdup(entity->d_name);
			files = files->next;
		}
	}
	return (head);
}

char	*ft_strfind(const char *big, const char *little, size_t len, int stp)
{
	size_t	i;
	int		j;
	char	*pt;

	i = 0;
	pt = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (len && big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			pt = (char *)big + i;
			j = 0;
			while (big[i + j] == little[j] && i + j < len)
			{
				if (!little[j + 1] || stp <= j)
					return (pt);
				j++;
			}
			pt = 0;
		}
		i++;
	}
	return (NULL);
}

int	there_is(char *to_find, char *str, t_var *var)
{
	char	*line;
	int		i;

	i = 0;
	if (ft_strlen(str) < var->i)
		return (0);
	else if (ft_strfind(str, to_find, ft_strlen(str), var->end - var->start))
		return (1);
	return (0);
}

void	inti_var_to_0(t_var *var)
{
	var->i = 0;
	var->j = 0;
	var->counter = 0;
	var->flag = 0;
}

void	skip_q(char *line, int *i, char c)
{
	*i = *i + 1;
	while (line[*i] && line[*i] != c)
		*i = *i + 1;
	if (line[*i] && line[*i] == '\'')
		skip_q(line, i, '\'');
	if (line[*i] && line[*i] == '\"')
		skip_q(line, i, '\"');
}

// int	ct(char *line, char *cmp)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// }

void	search_for_same_files(char **to_find, t_filename *files, t_var *var)
{
	int			i;
	int			counter;
	t_filename	*tmp;
	int			j = 0;

	i = 0;
	tmp = files;
	counter = 0;
	while (to_find[i])
	{
		files = tmp;
		while (files)
		{
			if (ft_strlen(files->name) >= ft_strlen(to_find[i]) && ft_strlen(files->name) >= files->counter)
			{
				printf("%s\n",&files->name[files->counter]);
				counter = found_it(&files->name[files->counter], to_find[i], ft_strlen(files->name));
				if (!counter)
					files->usable = 0;
				else if (i == 0 && var->check && ft_strncmp(files->name, to_find[0], ft_strlen(to_find[0])))
					files->usable = 0;
				else if (!to_find[i + 1] && var->end && ft_strncmp(&files->name[ft_strlen(files->name) - files->counter], to_find[0], ft_strlen(to_find[0])))
					files->usable = 0;
				else
					files->counter = counter;
			}
			else
				files->usable = 0;
			files = files->next;
		}
		i++;
	}
}

void	store_datas(char **str, char *line, int *i, int *j)
{
	*i = *i + 1;
	while (line[*i] && line[*i] != '\'')
	{
		*str[*j] = line[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
	*i = *i + 1;
	if (line[*i] == '\"')
		store_datad(str, line, i, j);
	*str[*j] = '\0';
}

void	store_datad(char **str, char *line, int *i, int *j)
{
	*i = *i + 1;
	while (line[*i] && line[*i] != '\"')
	{
		*str[*j] = line[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
	*i = *i + 1;
	if (line[*i] == '\'')
		store_datas(str, line, i, j);
	*str[*j] = '\0';
}

char	*chars(char *line, t_var *var)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	k = 0;
	if (!line || line[var->start] == '\0' || line[var->start] == ' ')
	{
		var->end = 1;
		return (NULL);
	}
	if (line[var->start] == '*')
	{
		while (line[var->start] && line[var->start] == '*')
			var->start++;
		if (!line[var->start] || line[var->start] == ' ')
		{
			if (line[var->start] == ' ')
				var->end = 1;
			var->i = var->start;
			return (NULL);
		}
	}
	i = var->start;
	while (line[i] && line[i] != '*')
		i++;
	str = malloc(sizeof(char) * i - var->start + 1);
	if (!str)
		return (NULL);
	j = 0;
	i = var->start;
	while (line[i] && line[i] != '*' && \
		line[i] != ' ')
	{
		// if (line[i] == '\'')
		// {
		// 	var->start += 2;
		// 	store_datas(&str, line, &i, &j);
		// }
		// if (!line[i] || line[i] == '*')
		// 	break ;
		// if (line[i] == '\"' || line[i] == '*')
		// 	store_datad(&str, line, &i, &j);
		// if (!line[i])
		// 	break ;
		str[j] = line[i];
		i++;
		j++;
	}
	str[j] = '\0';
	var->start += ft_strlen(str);
	return (str);
}

void	skip_najmat(char *line, int *j)
{
	while (line[*j] && line[*j] == '*')
		*j = *j + 1;
}

void	skip_char(char *line, int *j, int *i)
{
	*i = *i + 1;
	while (line[*j] && line[*j] != '*' && line[*j] != ' ')
		*j = *j + 1;
}

int	num_of_char(char *line)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (line[j] && line[j] != ' ')
	{
		if (line[j] == '*')
			skip_najmat(line, &j);
		if (line[j] && line[j] != '*')
			skip_char(line, &j, &i);
		if (!line[j])
			return (i);
	}
	return (i);
}

char	**to_find_str(char *line, t_var *var)
{
	char	**find;
	int		num_to_search;
	int		i;

	i = 0;
	num_to_search = num_of_char(&line[var->start]);
	find = malloc(sizeof(char *) * num_to_search + 1);
	// printf("%d!\n", num_to_search);
	while (i < num_to_search)
	{
		find[i] = chars(line, var);
		i++;
	}
	find[i] = NULL;
	return (find);
}

char	*change_line(char *line, t_filename *files, t_var *var)
{
	int	i;
	int	j;

	j = 0;
	i = var->j;
	while (line[i] && line[i] != ' ')
		i++;
	i = i - var->j;
	while (files)
	{
		if (files->usable == 1)
		{
			line = ft_strreplace_no_q(files->name, line, i, var->j);
			var->i += ft_strlen(files->name) + 3 - i;
			var->j += ft_strlen(files->name) + 3;
			i = 0;
		}
		files = files->next;
	}
	return (line);
}

char	*wild_card_line(char *line, t_var *var, t_filename *files)
{
	char		**to_find;
	int			j = 0;

	printf("|%s|\n", &line[var->j]);
	to_find = to_find_str(line, var);
	// printf("%d\n", var->end);
	while (to_find[j])
	{
		printf(":%s:\n", to_find[j]);
		j++;
	}
	search_for_same_files(to_find, files, var);
	line = change_line(line, files, var);
	var->check = 1;
	var->end = 0;
	while (files)
	{
		files->usable = 1;
		files->counter = 0;
		files = files->next;
	}
	return (line);
}

char	*handle_wildcard(char *line)
{
	t_var		*var;
	t_filename	*files;

	if (!line)
		return (NULL);
	files = get_files_name();
	init_var_2(&var);
	if (line[0] == '*')
		var->check = 0;
	line = wild_card_line(line, var, files);
	// while (line[var->i])
	// {
	// 	if (line[var->i] == ' ')
	// 	{
	// 		var->j = var->i + 1;
	// 		if (line[var->j] == '*')
	// 			var->check = 0;
	// 		var->start = var->i + 1;
	// 	}
	// 	if (line[var->i] == '*')
	// 		line = wild_card_line(line, var, files);
	// 	if (!line[var->i])
	// 		break ;
	// 	if (line[var->i] == ' ')
	// 	{
	// 		var->j = var->i + 1;
	// 		if (line[var->j] == '*')
	// 			var->check = 0;
	// 		var->start = var->i + 1;
	// 	}
	// 	var->i++;
	// }
	printf("%s--\n", line);
	// while (files)
	// {
	// 	printf("%s === %d \n", files->name, files->usable);
	// 	files = files->next;
	// }
	free(var);
	return (line);
}
		// if (line[var->i] == '\"')
		// 	skip_q(line, &var->i, '\"');
		// if (line[var->i] == '\'')
		// 	skip_q(line, &var->i, '\'');
		// if (!line[var->i])
		// 	break ;

int	main(int ac, char **av)
{
	char	*line;

	line = handle_wildcard(av[1]);
}

// void	compare_value(t_token *token, t_filename *file, t_var *var)
// {
// 	while (file)
// 	{
// 		if (there_is(&token->data[var->i], file->name, var))
// 			file->flag = 1;
// 		file = file->next;
// 	}
// }

// void	ft_wildcard(t_token *token, t_var *var, t_filename *files)
// {
// 	var->i = var->counter;
// 	// if (!token->data[var->counter])
// 	// 	return ;
// 	while (token->data[(var->counter)] && token->data[(var->counter)] != '*')
// 		var->counter = var->counter + 1;
// 	// if (!token->data[var->counter])
// 	// 	return ;
// 	var->j = var->counter;
// 	while (token->data[(var->counter)] && token->data[(var->counter)] == '*')
// 		var->counter = var->counter + 1;
// 	// if (!token->data[var->counter])
// 	// 	return ;
// 	compare_value(token, files, var);
// }

// static char	**full_array(int i)
// {
// 	char			**arr;
// 	DIR				*dir;
// 	struct dirent	*entity;

// 	arr = malloc(sizeof(char *) * (i + 1));
// 	if (!arr)
// 		return (NULL);
// 	dir = opendir(".");
// 	if (dir == NULL)
// 		return (NULL);
// 	i = 0;
// 	entity = readdir(dir);
// 	while (entity)
// 	{
// 		arr[i] = ft_strdup(entity->d_name);
// 		entity = readdir(dir);
// 		i++;
// 	}
// 	arr[i] = NULL;
// 	return (arr);
// }

// static void	calcul(char *cmd, char **arr, int start, int end)
// {
// 	int		i;
// 	int		j;
// 	char	**holder;

// 	i = 0;
// 	j = 0;
// 	while (arr[i])
// 		i++;
// 	holder = malloc(sizeof(char *) * (i + 1));
// 	if (!holder)
// 		return ;
// 	i = 0;
// 	while (arr[i])
// 	{
// 		if (is_eqaul())
// 			holder[j] == arr[i];
// 		i++;
// 	}
	
// }
