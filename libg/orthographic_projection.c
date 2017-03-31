/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orthographic_projection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:48:24 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/23 17:48:25 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

static t_vec3fc	camera_transform(t_camera cam, t_vec3fc point)
{
	t_vec3fc new_point;

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

t_vec3fc		orthographic_projection(t_scene scene, t_vec3fc point)
{
	t_vec3fc	new_point;
	t_vec3fc	projection;
	t_camera	cam;

	cam = *(scene.camera);
	point.y *= -1;
	point.x += scene.origin_point.x;
	point.y += scene.origin_point.y;
	point.z += scene.origin_point.z;
	new_point = camera_transform(cam, point);
	if (new_point.z > 0)
		return (vec3fc(0, 0, 0, 0x4F000000));
	projection.x = scene.scale.x * new_point.x + 500;
	projection.y = scene.scale.y * new_point.y + 500;
	projection.z = new_point.z;
	projection.color = point.color;
	return (projection);
}
