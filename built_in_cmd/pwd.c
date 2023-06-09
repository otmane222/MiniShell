/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:33:24 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/07 21:07:38 by oaboulgh         ###   ########.fr       */
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
	free(str);
	write(outfile, "\n", 1);
}
