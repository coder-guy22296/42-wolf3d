/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 15:30:09 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/03 16:14:53 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*out;
	int		index;

	if (s == NULL || f == NULL)
		return (NULL);
	if (!(out = ft_strdup(s)))
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		out[index] = f(s[index]);
		index++;
	}
	return (out);
}
