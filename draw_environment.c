/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:03:33 by cyildiri          #+#    #+#             */
/*   Updated: 2017/03/30 18:05:12 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_column(t_frame *frame, int col_num, int length, int color)
{
	int	i;
	int	y_offset;

	y_offset = (frame->height - length) / 2;
	i = 0;
	while (i < length)
	{
		frame_draw_pixel(frame, col_num, i + y_offset, color);
		i++;
	}
}

void	draw_floor_ceiling(t_frame *frame, int floor_color, int ceil_color)
{
	t_vec2i	cur_pixel;

	cur_pixel.y = 0;
	while (cur_pixel.y < frame->height)
	{
		cur_pixel.x = 0;
		while(cur_pixel.x < frame->width)
		{
			if (cur_pixel.y <= frame->height / 2)
				frame_draw_pixel(frame, cur_pixel.x, cur_pixel.y, floor_color);
			else
				frame_draw_pixel(frame, cur_pixel.x, cur_pixel.y, ceil_color);
			cur_pixel.x++;
		}
		cur_pixel.y++;
	}
}

void	draw_walls(t_frame *frame, t_frame *rc_map, t_player *player)
{
	double	cur_dir;
	int		cur_column;
	double	distance;
	double	column_height;
	int		color;

	cur_dir = player->direction + (player->fov / 2.0f);
	cur_column = 0;
	while (cur_column < frame->width)
	{
		cur_dir -= player->fov / (double)frame->width;
		distance = cast_ray(rc_map, player->position, cur_dir, &color);
		column_height = ((double)frame->height
			/ (distance * cos(player->direction - cur_dir)));
		draw_column(frame, cur_column, (int)column_height, color);
		cur_column++;
	}
}
