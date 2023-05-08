/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:36:49 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/05/02 15:36:49 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lk(void)
{
	system("leaks a.out");
}

void	call_d()
{
	char	*str;

	str = getenv("USER");
    printf("%s\n", str);
}

int main()
{
    // char	*line;
	char	*str;

    // line = readline("Minishell > ");
	atexit(lk);
	call_d();
}
