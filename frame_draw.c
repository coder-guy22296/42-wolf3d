/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:05:58 by cyildiri          #+#    #+#             */
/*   Updated: 2017/03/30 18:06:02 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		frame_draw_pixel(t_frame *frame, int x, int y, int color)
{
	unsigned int	*image;
	int				pos;

	image = (unsigned int *)frame->image;
	if (x < 0 || x >= frame->width
		|| y < 0 || y >= frame->height)
	{
		return (1);
	}
	pos = x + (y * frame->line_size / 4);
	image[pos] = (unsigned int)color;
	return (0);
}
void	frame_draw_square(t_frame *frame, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			frame_draw_pixel(frame, x + j, y + i, 0x00FFFFFF);
			j++;
		}
		i++;
	}
}

void	frame_apply_alpha(t_frame *frame, double alpha)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < frame->height)
	{
		j = 0;
		while (j < frame->width)
		{
			color = frame_get_pixel(frame, j, i);
			frame_draw_pixel(frame, j, i, apply_alpha(color, alpha));
			j++;
		}
		i++;
	}
}

void	frame_clear(t_frame *frame)
{
	int	i;
	int	j;

	i = 0;
	while (i < frame->height)
	{
		j = 0;
		while (j < frame->width)
		{
			frame_draw_pixel(frame, j, i, 0xFF000000);
			j++;
		}
		i++;
	}
}
