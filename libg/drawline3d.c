/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:47:01 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/25 14:47:04 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

void	drawline3d(t_renderer *renderer, t_vec3fc point_a, t_vec3fc point_b)
{
	t_vec3fc	point1;
	t_vec3fc	point2;

	point1 = renderer->scene->projection_method(*renderer->scene, point_a);
	point2 = renderer->scene->projection_method(*renderer->scene, point_b);
	if (!(point1.x < 0 - renderer->win_x * 0.25
		|| point1.x > renderer->win_x * 1.25
		|| point2.y < 0 - renderer->win_y * 0.25
		|| point2.y > renderer->win_y * 1.25
		|| point1.color == 0x4F000000 || point2.color == 0x4F000000
		|| (int)point_a.z == -2147483648 || (int)point_b.z == -2147483648
		|| (int)point1.z == -2147483648 || (int)point2.z == -2147483648))
	{
		drawline(renderer, point1, point2);
	}
}
