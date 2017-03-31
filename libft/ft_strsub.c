/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 16:41:11 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/03 17:08:48 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	index;
	int				i;
	char			*out_str;

	if (s == NULL)
		return (NULL);
	if (!(out_str = ft_strnew(len)))
		return (NULL);
	index = start;
	i = 0;
	while (index < start + len)
	{
		out_str[i] = s[index];
		i++;
		index++;
	}
	return (out_str);
}
