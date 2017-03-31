/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 13:04:12 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/27 13:04:13 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

static void	del_wrapper(void *addr, size_t size)
{
	size = 0;
	del_3d_object((t_3d_object *)addr);
}

void		del_scene(t_scene *scene)
{
	ft_memdel((void **)&(scene->camera));
	ft_lstdel(&(scene->objects), del_wrapper);
	ft_memdel((void **)&scene);
}
