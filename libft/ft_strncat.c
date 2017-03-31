/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 21:57:00 by cyildiri          #+#    #+#             */
/*   Updated: 2016/09/26 14:14:49 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		index;
	size_t	i;

	index = 0;
	while (s1[index] != '\0')
		index++;
	i = 0;
	while (i < n && s2[i] != '\0')
	{
		s1[index] = s2[i];
		index++;
		i++;
	}
	s1[index] = '\0';
	return (s1);
}
