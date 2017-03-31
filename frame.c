#include "wolf3d.h"
#include <stdlib.h>

t_frame		*new_tframe(t_rc_renderer *rend, int height, int width)
{
	t_frame	*frame;

	if(!(frame = (t_frame *)ft_memalloc(sizeof(t_frame))))
		return (0);
	frame->id = mlx_new_image(rend->mlx, width, height);
	frame->image = mlx_get_data_addr(
		frame->id,
		&frame->color_depth,
		&frame->line_size,
		&frame->endien);
	frame->height = height;
	frame->width = width;
	return (frame);
}

void		frame_delete(t_rc_renderer *rend, t_frame **delete_me)
{
	mlx_destroy_image(rend->mlx, (*delete_me)->id);
	free(*delete_me);
	*delete_me = NULL;
}

t_frame		*frame_resize(t_rc_renderer *rend, t_frame *orig, double scaling)
{
	t_vec2i cur;
	t_frame *scaled_frame;
	t_vec2i size;
	t_vec2i new_pos;

	size.y = orig->height * scaling;
	size.x = orig->width * scaling;
	scaled_frame = new_tframe(rend, size.y, size.x);
	cur.y = 0;
	while (cur.y < orig->height)
	{
		cur.x = 0;
		while (cur.x < orig->width)
		{
			new_pos.x = cur.x * scaling;
			new_pos.y = cur.y * scaling;
			if (frame_get_pixel(orig, cur.x, cur.y) != 0)
			{
				frame_draw_square(scaled_frame, new_pos.x, new_pos.y, scaling);
			}
			cur.x++;
		}
		cur.y++;
	}
	return (scaled_frame);
}

int			frame_get_pixel(t_frame *frame, int x, int y)
{
	unsigned int	*image;
	int				pos;

	image = (unsigned int *)frame->image;
	if (x < 0 || x >= frame->width || y < 0 || y >= frame->height)
	{
		return (1);
	}
	pos = x + (y * frame->line_size / 4);
	return (image[pos]);
}
