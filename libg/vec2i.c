/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 21:01:16 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/21 21:10:58 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

t_vec2i	*new_vec2i(int x, int y)
{
	t_vec2i	*point;

	if (!(point = (t_vec2i *)ft_memalloc(sizeof(t_vec2i))))
		return (NULL);
	point->x = x;
	point->y = y;
	return (point);
}

t_vec2i	vec2i(int x, int y)
{
	t_vec2i point;

	point.x = x;
	point.y = y;
	return (point);
}
