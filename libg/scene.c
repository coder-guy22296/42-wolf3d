/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 22:30:51 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/21 22:37:25 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

t_scene	*new_scene(struct s_vec3fc (*projection)(t_scene scene, t_vec3fc point),
					int frame_height, int frame_width)
{
	t_scene *scene3d;

	if (!(scene3d = (t_scene *)ft_memalloc(sizeof(t_scene))))
		return (NULL);
	scene3d->projection_method = projection;
	scene3d->cur_frame = new_frame(frame_height, frame_width);
	scene3d->origin_point = vec3f(0, 0, 0);
	scene3d->active_obj = 0;
	scene3d->scale = vec3f(13, 13, 13);
	return (scene3d);
}

t_scene	scene(struct s_vec3fc (*projection)(t_scene scene, t_vec3fc point),
					int frame_height, int frame_width)
{
	t_scene scene3d;

	scene3d.projection_method = projection;
	scene3d.cur_frame = new_frame(frame_height, frame_width);
	scene3d.origin_point = vec3f(0, 0, 0);
	scene3d.scale = vec3f(13, 13, 13);
	return (scene3d);
}
