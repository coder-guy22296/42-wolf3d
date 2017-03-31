/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 21:43:21 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/04 16:56:08 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_start(char const *s, int *index, int low)
{
	while (s[*index] != '\0')
	{
		if (!ft_isspace(s[*index]) && low == -1)
			low = *index;
		(*index)++;
	}
	(*index)--;
	return (low);
}

static int	ft_find_end(char const *s, int *index, int high)
{
	while (*index >= 0 && high != *index)
	{
		if (!ft_isspace(s[*index]) && high == -1)
		{
			high = *index;
			break ;
		}
		(*index)--;
	}
	return (high);
}

static char	*ft_copy_str(char const *s, char *out_str, int high, int low)
{
	int len;
	int index;
	int i;

	len = (high + 1) - low;
	index = high;
	i = len - 1;
	while (index >= low)
	{
		out_str[i] = s[index];
		i--;
		index--;
	}
	return (out_str);
}

char		*ft_strtrim(char const *s)
{
	int		index;
	char	*out_str;
	int		high;
	int		low;

	if (s == NULL)
		return (NULL);
	index = 0;
	low = ft_find_start(s, &index, -1);
	high = ft_find_end(s, &index, -1);
	if (low == high)
	{
		if (!(out_str = ft_strnew(0)))
			return (NULL);
	}
	else
	{
		if (!(out_str = ft_strnew((high + 1) - low)))
			return (NULL);
		out_str = ft_copy_str(s, out_str, high, low);
	}
	return (out_str);
}
