/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:33:24 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/30 21:15:02 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_pwd(int outfile, t_env **env)
{
	static char	*path;
	char		*str;

	str = getcwd(NULL, 0);
	if (!str)
		str = ft_getenv("PWD", *env);
	else
		path = str;
	ft_putstr_fd(str, outfile);
	write(outfile, "\n", 1);
}
