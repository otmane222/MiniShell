/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:15:35 by nakebli           #+#    #+#             */
/*   Updated: 2022/10/29 14:36:37 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	size;
	size_t	sz;

	substr = NULL;
	sz = 0;
	if (s == NULL)
		return (ft_strdup(""));
	sz = ft_strlen((char *)s);
	if (start + len <= sz)
		substr = malloc(sizeof(char) * (len + 1));
	else if (start < sz && start + len > sz)
		substr = malloc(sizeof(char) * (sz - start));
	else
		return (ft_strdup(""));
	if (substr == NULL)
		return (NULL);
	size = ft_strlen((char *)s + start);
	i = -1;
	while (++i < len && start < ft_strlen((char *)s))
		substr[i] = s[start++];
	substr[i] = '\0';
	return (substr);
}
