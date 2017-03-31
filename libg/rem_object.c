/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rem_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 15:41:56 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/26 15:41:58 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

static void	del_wrapper(void *addr, size_t size)
{
	size = 0;
	del_3d_object((t_3d_object *)addr);
}

void		rem_object(t_scene *scene, t_3d_object *obj)
{
	t_list *cur;

	cur = scene->objects;
	if (cur)
	{
		while (cur->next)
		{
			if (ft_memcmp(cur->content, obj, sizeof(t_3d_object)) == 0)
			{
				ft_lstdelone(&cur, del_wrapper);
			}
			cur = cur->next;
		}
	}
}
