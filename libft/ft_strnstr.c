/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 14:15:39 by cyildiri          #+#    #+#             */
/*   Updated: 2016/09/28 20:25:42 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*ptr;
	int		index;
	int		lil_len;

	index = 0;
	lil_len = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	while (index < (int)len && big[index] != '\0')
	{
		if (big[index] == little[0])
		{
			ptr = (char *)&big[index];
			if (lil_len <= (int)len - index)
				if (lil_len <= (int)ft_strlen(big) - index)
					if (!ft_memcmp(ptr, little, ft_strlen(little)))
						return (ptr);
		}
		index++;
	}
	return (NULL);
}
