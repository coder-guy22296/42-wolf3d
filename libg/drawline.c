/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:46:39 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/25 14:46:41 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "libgraphics.h"

static t_line	c_line(t_vec3fc point_a, t_vec3fc point_b)
{
	t_line line;

	if (point_a.x > point_b.x)
	{
		line.start = point_a;
		line.end = point_b;
	}
	else
	{
		line.start = point_b;
		line.end = point_a;
	}
	line.delta.x = (int)line.end.x - (int)line.start.x;
	line.delta.y = (int)line.end.y - (int)line.start.y;
	line.slope = (line.delta.x == 0)
						? 0 : (double)line.delta.y / (double)line.delta.x;
	line.cur.x = (int)line.start.x;
	line.cur.y = (int)line.start.y;
	line.dir.x = (line.delta.x < 0) ? -1 : 1;
	line.dir.y = (line.delta.y < 0) ? -1 : 1;
	return (line);
}

static void		drawline_xmajor(t_renderer *renderer, t_line line)
{
	double	deltaerr;
	double	error;

	error = -1.0;
	deltaerr = fabs((double)line.delta.x / (double)line.delta.y);
	while (line.cur.y != (int)line.end.y)
	{
		if (line.cur.y == line.start.y)
			error += deltaerr;
		frame_pixel_put(renderer->scene, vec2fc(line.cur.x, line.cur.y,
			blend(line.start.color, line.end.color,
			(fabsf((float)line.cur.y - line.start.y)) / abs(line.delta.y))));
		error += deltaerr;
		if (error >= 0.0)
		{
			line.cur.x += line.dir.x;
			error -= 1.0;
		}
		line.cur.y += line.dir.y;
	}
}

static void		drawline_ymajor(t_renderer *renderer, t_line line)
{
	double	deltaerr;
	double	error;

	error = -1.0;
	deltaerr = fabs(line.slope);
	error += deltaerr;
	while (line.cur.x != (int)line.end.x)
	{
		frame_pixel_put(renderer->scene, vec2fc(line.cur.x, line.cur.y,
			blend(line.start.color, line.end.color,
			(fabsf((float)line.cur.x - line.start.x)) / abs(line.delta.x))));
		error += deltaerr;
		if (error >= 0.0)
		{
			line.cur.y += line.dir.y;
			error -= 1.0;
		}
		line.cur.x += line.dir.x;
	}
}

void			drawline(t_renderer *renderer, t_vec3fc point_a,
												t_vec3fc point_b)
{
	t_line line;

	line = c_line(point_a, point_b);
	if ((fabs(line.slope) > 1.0 || line.delta.x == 0))
		drawline_xmajor(renderer, line);
	else if (fabs(line.slope) <= 1.0)
		drawline_ymajor(renderer, line);
}
