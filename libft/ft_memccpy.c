/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 21:21:36 by cyildiri          #+#    #+#             */
/*   Updated: 2016/09/26 14:27:37 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			index;
	unsigned char	*src_ptr;
	unsigned char	*dst_ptr;

	index = 0;
	src_ptr = (unsigned char *)src;
	dst_ptr = (unsigned char *)dst;
	while (index < n)
	{
		dst_ptr[index] = src_ptr[index];
		if (dst_ptr[index] == (unsigned char)c)
			return (&dst_ptr[index + 1]);
		index++;
	}
	if (index == n)
		return (NULL);
	else
		return (&dst_ptr[index]);
}
