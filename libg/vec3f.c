/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 21:14:22 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/21 21:20:42 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

t_vec3fc	*new_vec3f(float x, float y, float z)
{
	t_vec3fc *point;

	if (!(point = (t_vec3fc *)ft_memalloc(sizeof(t_vec3fc))))
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
}

t_vec3fc	vec3f(float x, float y, float z)
{
	t_vec3fc point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_vec3fc	vec3fc(float x, float y, float z, int color)
{
	t_vec3fc point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.color = color;
	return (point);
}
