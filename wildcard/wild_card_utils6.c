/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:28:25 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/06/25 17:28:36 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	del_tokenx(t_token **tok)
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!tok || !(*tok))
		return ;
	tmp = (*tok)->next;
	tmp2 = (*tok)->prev;
	free((*tok)->data);
	free((*tok));
	(*tok) = NULL;
	if (tmp)
		tmp->prev = tmp2;
	if (tmp2)
		tmp2->next = tmp;
}

t_token	*init_token_wild(void)
{
	t_token	*token;

	token = malloc (sizeof(t_token));
	if (!token)
		return (NULL);
	token->data = NULL;
	token->next = NULL;
	token->flag = -9;
	token->type = -10;
	token->prev = NULL;
	return (token);
}
