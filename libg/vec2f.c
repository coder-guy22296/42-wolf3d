/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 21:10:20 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/21 21:14:00 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

t_vec2fc	*new_vec2f(float x, float y)
{
	t_vec2fc	*point;

	if (!(point = (t_vec2fc *)ft_memalloc(sizeof(t_vec2fc))))
		return (NULL);
	point->x = x;
	point->y = y;
	return (point);
}

t_vec2fc	vec2f(float x, float y)
{
	t_vec2fc	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_vec2fc	vec2fc(float x, float y, int color)
{
	t_vec2fc	point;

	point.x = x;
	point.y = y;
	point.color = color;
	return (point);
}
