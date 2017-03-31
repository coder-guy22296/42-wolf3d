/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lmapremove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 13:23:21 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/26 13:23:22 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lmapremove(t_lmap **map, void const *key, void (*del_key)(void *),
					void (*del_content)(void *))
{
	t_lmap *cur;
	t_lmap *last;

	cur = *map;
	last = *map;
	while (cur)
	{
		if (ft_memcmp(key, cur->key, cur->key_size) == 0)
		{
			del_content(cur->content);
			del_key(cur->key);
			if (last != *map)
				last->next = cur->next;
			else
				*map = cur->next;
			ft_memdel((void **)&cur);
			return (1);
		}
		last = cur;
		cur = cur->next;
	}
	return (0);
}
