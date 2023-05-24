/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:33:24 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/23 22:09:01 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_pwd(int outfile)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putstr_fd(path, outfile);
	write(outfile, "\n", 1);
}
