/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/02 21:28:59 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/03 13:13:29 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char	*mem;
	int		i;

	if (!(mem = (char *)malloc(size)))
		return (NULL);
	i = 0;
	while (i < (int)size)
	{
		mem[i] = '\0';
		i++;
	}
	return (mem);
}
