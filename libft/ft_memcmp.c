/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 19:43:55 by cyildiri          #+#    #+#             */
/*   Updated: 2016/09/28 16:14:49 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			index;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (n == 0)
		return (0);
	index = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (index < n && ptr1[index] == ptr2[index])
	{
		if (index == n - 1)
			return (0);
		index++;
	}
	if (ptr1[index] != ptr2[index])
		return ((int)ptr1[index] - (int)ptr2[index]);
	else
		return (0);
}
