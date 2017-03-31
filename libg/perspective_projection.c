/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_projection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:48:02 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/23 17:48:03 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libgraphics.h"

static t_vec3fc	camera_transform(t_camera cam, t_vec3fc point)
{
	t_vec3fc	new_point;

	new_point.x = (float)(cos(cam.loc.rotation.y) * (sin(cam.loc.rotation.z)
				* (point.y - cam.loc.position.y) + cos(cam.loc.rotation.z)
				* (point.x - cam.loc.position.x)) - sin(cam.loc.rotation.y)
				* (point.z - cam.loc.position.z));
	new_point.y = (float)(sin(cam.loc.rotation.x) * (cos(cam.loc.rotation.y)
				* (point.z - cam.loc.position.z) + sin(cam.loc.rotation.y)
				* (sin(cam.loc.rotation.z) * (point.y - cam.loc.position.y)
				+ cos(cam.loc.rotation.z) * (point.x - cam.loc.position.x)))
				+ cos(cam.loc.rotation.x) * (cos(cam.loc.rotation.z)
				* (point.y - cam.loc.position.y) - sin(cam.loc.rotation.z)
				* (point.x - cam.loc.position.x)));
	new_point.z = (float)(cos(cam.loc.rotation.x) * (cos(cam.loc.rotation.y)
				* (point.z - cam.loc.position.z) + sin(cam.loc.rotation.y)
				* (sin(cam.loc.rotation.z) * (point.y - cam.loc.position.y)
				+ cos(cam.loc.rotation.z) * (point.x - cam.loc.position.x)))
				- sin(cam.loc.rotation.x) * (cos(cam.loc.rotation.z)
				* (point.y - cam.loc.position.y) - sin(cam.loc.rotation.z)
				* (point.x - cam.loc.position.x)));
	return (new_point);
}

static t_vec2fc	project_point(t_camera cam, t_vec3fc new_point)
{
	t_vec2fc	projection;

	projection.x = (float)(((cam.viewer.z / fabs(new_point.z))
							* new_point.x) - cam.viewer.x);
	projection.y = (float)(((cam.viewer.z / fabs(new_point.z))
							* new_point.y) - cam.viewer.y);
	return (projection);
}

t_vec3fc		perspective_projection(t_scene scene, t_vec3fc point)
{
	t_vec3fc	new_point;
	t_vec2fc	projection;
	t_vec2fc	normalized_points;
	t_vec3fc	rasterized_points;
	t_camera	cam;

	cam = *(scene.camera);
	point.x += scene.origin_point.x;
	point.y += scene.origin_point.y;
	point.z += scene.origin_point.z;
	new_point = camera_transform(cam, point);
	if (new_point.z > 0.0)
		return (vec3fc(0, 0, 0, 0x4F000000));
	projection = project_point(cam, new_point);
	normalized_points.x = (projection.x + 1) / 2;
	normalized_points.y = (1 - projection.y) / 2;
	rasterized_points.x = (int)(normalized_points.x * 1000);
	rasterized_points.y = (int)(normalized_points.y * 1000);
	rasterized_points.z = new_point.z;
	rasterized_points.color = point.color;
	return (rasterized_points);
}
