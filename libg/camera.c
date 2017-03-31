/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 21:51:51 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/21 22:01:14 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

t_camera	*new_camera(t_vec6f camera_loc, t_vec3fc viewer_loc)
{
	t_camera *cam;

	if (!(cam = (t_camera *)ft_memalloc(sizeof(t_camera))))
		return (NULL);
	cam->loc = camera_loc;
	cam->viewer = viewer_loc;
	return (cam);
}

t_camera	camera(t_vec6f camera_loc, t_vec3fc viewer_loc)
{
	t_camera cam;

	cam.loc = camera_loc;
	cam.viewer = viewer_loc;
	return (cam);
}
