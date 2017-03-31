/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 13:12:35 by cyildiri          #+#    #+#             */
/*   Updated: 2016/09/26 14:38:53 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		index;

	ptr = NULL;
	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == (char)c)
			ptr = (char *)&s[index];
		index++;
	}
	if (s[index] == (char)c)
		ptr = (char *)&s[index];
	return (ptr);
}
