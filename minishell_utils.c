/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:35:23 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/04/11 12:30:56 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var(t_var **var)
{
	*var = malloc(sizeof(t_var));
	(*var)->i = -1;
	(*var)->j = 0;
	(*var)->check = 1;
	(*var)->status = 0;
	(*var)->counter = 0;
	(*var)->qoutes_flag = 0;
	(*var)->start = 0;
	(*var)->end = 0;
}
