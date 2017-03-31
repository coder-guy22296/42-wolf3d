/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 16:16:42 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/03 16:21:49 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*out;

	if (s == NULL || f == NULL)
		return (NULL);
	if (!(out = ft_strdup(s)))
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		out[index] = f(index, s[index]);
		index++;
	}
	return (out);
}
