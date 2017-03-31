/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 17:09:35 by cyildiri          #+#    #+#             */
/*   Updated: 2016/09/26 14:26:15 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptr;
	size_t	index;

	ptr = (char *)s;
	index = 0;
	while (index < n)
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
		index++;
	}
	return (NULL);
}
