/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_pixel_put.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 21:05:44 by cyildiri          #+#    #+#             */
/*   Updated: 2016/12/15 21:05:46 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"
#include <stdlib.h>

int	frame_pixel_put(t_scene *scene, t_vec2fc place_me)
{
	t_frame			*frame;
	unsigned int	*image;
	int				pos;

	frame = &(scene->cur_frame);
	image = (unsigned int *)frame->image;
	if (place_me.x < 0 || place_me.x >= scene->cur_frame.width
		|| place_me.y < 0 || place_me.y >= scene->cur_frame.height
		|| place_me.color == 0x4F000000)
	{
		return (1);
	}
	pos = place_me.x + (place_me.y * frame->line_size / 4);
	image[pos] = (unsigned int)place_me.color;
	return (0);
}
