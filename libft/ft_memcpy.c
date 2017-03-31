/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 20:47:48 by cyildiri          #+#    #+#             */
/*   Updated: 2016/09/26 15:52:27 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
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
		index++;
	}
	return (dst);
}
