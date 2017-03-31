/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 22:05:56 by cyildiri          #+#    #+#             */
/*   Updated: 2016/09/26 12:34:02 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int index;
	int max_cpy;
	int dst_len;
	int i;

	dst_len = ft_strlen(dst);
	index = 0;
	while (dst[index] != '\0')
		index++;
	max_cpy = (size - dst_len - 1);
	i = 0;
	while (i < max_cpy)
	{
		dst[index] = src[i];
		index++;
		i++;
	}
	dst[index] = '\0';
	if ((int)size < dst_len)
		return (size + ft_strlen(src));
	else
		return (dst_len + ft_strlen(src));
}
