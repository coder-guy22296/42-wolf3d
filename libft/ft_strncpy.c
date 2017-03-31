/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 11:40:26 by cyildiri          #+#    #+#             */
/*   Updated: 2016/09/27 19:45:49 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	index;
	size_t	i;

	index = 0;
	i = 0;
	while (index < len)
	{
		if (src[i] != '\0')
		{
			dst[index] = src[i];
			i++;
		}
		else
			dst[index] = '\0';
		index++;
	}
	return (dst);
}
