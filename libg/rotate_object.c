/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:49:15 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/23 17:49:16 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

static void	rotate_x(t_vec3fc original, t_vec3fc rotation, t_vec3fc *new_point)
{
	float	sin_t;
	float	cos_t;

	sin_t = sin(rotation.x);
	cos_t = cos(rotation.x);
	new_point->y = original.y * cos_t - original.z * sin_t;
	new_point->z = original.z * cos_t + original.y * sin_t;
}

static void	rotate_y(t_vec3fc original, t_vec3fc rotation, t_vec3fc *new_point)
{
	float	sin_t;
	float	cos_t;

	sin_t = sin(rotation.y);
	cos_t = cos(rotation.y);
	new_point->x = original.x * cos_t - original.z * sin_t;
	new_point->z = original.z * cos_t + original.x * sin_t;
}

static void	rotate_z(t_vec3fc original, t_vec3fc rotation, t_vec3fc *new_point)
{
	float	sin_t;
	float	cos_t;

	sin_t = sin(rotation.z);
	cos_t = cos(rotation.z);
	new_point->x = original.x * cos_t - original.y * sin_t;
	new_point->y = original.y * cos_t + original.x * sin_t;
}

void		rotate_object(t_3d_object *obj, t_vec3fc rotation)
{
	int	index;

	index = 0;
	while (index < obj->vertex_cnt)
	{
		if ((int)obj->vertices[index].z != -2147483648)
		{
			if (rotation.x)
				rotate_x(obj->vertices[index], rotation, &obj->vertices[index]);
			if (rotation.y)
				rotate_y(obj->vertices[index], rotation, &obj->vertices[index]);
			if (rotation.z)
				rotate_z(obj->vertices[index], rotation, &obj->vertices[index]);
		}
		index++;
	}
	obj->pos_vector.rotation.x += rotation.x;
	obj->pos_vector.rotation.y += rotation.y;
	obj->pos_vector.rotation.z += rotation.z;
}
