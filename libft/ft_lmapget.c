/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lmapget.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 14:10:03 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/26 14:10:08 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lmap	*ft_lmapget(t_lmap *map, void const *key)
{
	t_lmap *cur;

	cur = map;
	while (cur)
	{
		if (ft_memcmp(key, cur->key, cur->key_size) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
