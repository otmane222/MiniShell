/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:21:40 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/26 02:47:08 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	check_valid(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (12);
}

void	ret_check(char *str, t_env **env)
{
	ft_printf("minishell: warning: shell level");
	ft_printf("(%s) too high, resetting to 1\n", str);
	edit_env("SHLVL", ft_strdup("1"), env);
	free(str);
}

void	handle_shell_lvl(t_env **env)
{
	char		*str;
	char		*tmp;
	int			num;
	int			i;

	ft_init(env);
	str = ft_getenv("SHLVL", *env);
	if (!str)
		return (add_to_env(ft_strdup("SHLVL"), ft_strdup("1"), env));
	str = ft_strtrim(str, " \t\r\v\f");
	if (!check_valid(str))
		return (edit_env("SHLVL", ft_strdup("1"), env));
	if (str[0] == '-')
		return (edit_env("SHLVL", ft_strdup("0"), env));
	i = ft_strlen(str);
	num = ft_atoi(str);
	if (num >= 1000 && i >= 4)
		return (ret_check(str, env));
	if (num == 999)
		return (edit_env("SHLVL", ft_strdup(""), env), free(str));
	num += 1;
	tmp = ft_itoa(num);
	edit_env("SHLVL", tmp, env);
	return (free(str));
}
