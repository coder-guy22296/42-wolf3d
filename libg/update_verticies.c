/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_verticies.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 13:59:47 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/25 14:00:07 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

t_3d_object	update_verticies(t_3d_object *obj)
{
	int			index;
	t_vec3fc	rotation;

	rotation = obj->pos_vector.rotation;
	index = 0;
	while (index < obj->vertex_cnt)
	{
		obj->vertices[index].y = obj->vertices[index].y * cos(rotation.x);
		obj->vertices[index].z = obj->vertices[index].y * sin(rotation.x);
		obj->vertices[index].x = obj->vertices[index].x * cos(rotation.y);
		obj->vertices[index].z = obj->vertices[index].x * sin(rotation.y);
		obj->vertices[index].x = obj->vertices[index].x * cos(rotation.z);
		obj->vertices[index].y = obj->vertices[index].x * sin(rotation.z);
		index++;
	}
	return (*obj);
}
