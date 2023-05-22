/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:44:45 by nakebli           #+#    #+#             */
/*   Updated: 2023/05/22 16:13:58 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_op(int a)
{
	if (a == RED_IN || a == RED_OUT || a == D_RED_IN || \
		a == D_RED_OUT || a == PIPE || a == DPIPE \
		|| a == D_AND)
		return (1);
	return (0);
}
