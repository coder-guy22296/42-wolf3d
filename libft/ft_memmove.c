/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 20:18:59 by cyildiri          #+#    #+#             */
/*   Updated: 2016/09/26 15:45:26 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int				index;
	unsigned char	*src_ptr;
	unsigned char	*dst_ptr;

	index = 0;
	src_ptr = (unsigned char *)src;
	dst_ptr = (unsigned char *)dst;
	if (src > dst)
		while (index < (int)len)
		{
			dst_ptr[index] = src_ptr[index];
			index++;
		}
	else if (dst > src)
	{
		index = (int)len - 1;
		while (index > -1)
		{
			dst_ptr[index] = src_ptr[index];
			index--;
		}
	}
	return (dst);
}
