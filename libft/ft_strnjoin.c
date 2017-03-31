/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:49:07 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/03 15:22:02 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	just like strjoin except it only joins part of the second string
**	will allocate enough memory for the first string + specified size of
**	the second string regardless of the actual lengh of the second string
*/

char	*ft_strnjoin(char const *s1, char const *s2, size_t s2size)
{
	char	*str_out;
	int		index;
	int		len;
	int		i;

	len = ft_strlen(s1) + s2size;
	if (!(str_out = ft_strnew(len)))
		return (NULL);
	index = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		str_out[index] = s1[i];
		i++;
		index++;
	}
	i = 0;
	while (s2[i] != '\0' && i < (int)s2size)
	{
		str_out[index] = s2[i];
		i++;
		index++;
	}
	str_out[index] = '\0';
	return (str_out);
}
