/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 13:44:46 by cyildiri          #+#    #+#             */
/*   Updated: 2016/09/28 13:22:21 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	char	*ptr;
	int		index;

	index = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[index] != '\0')
	{
		if (big[index] == little[0])
		{
			ptr = (char *)&big[index];
			if (!ft_memcmp(ptr, little, ft_strlen(little)))
				return (ptr);
		}
		index++;
	}
	return (NULL);
}
