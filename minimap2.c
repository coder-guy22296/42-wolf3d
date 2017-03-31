#include "wolf3d.h"

static void	drawray_xmajor(t_minimap *minimap, t_vec2i start, t_vec2d delta,
								  int color)
{
	double	deltaerr;
	double	error;
	t_vec2i cur;
	t_vec2i dir;

	cur = start;
	dir.x = (delta.x < 0) ? -1 : 1;
	dir.y = (delta.y < 0) ? -1 : 1;
	error = -1.0;
	deltaerr = fabs(delta.x / delta.y);
	error += deltaerr;
	while ((frame_get_pixel(minimap->map, cur.x, cur.y) & 0x00FFFFFF) == 0)
	{
		frame_draw_pixel(minimap->overlay, cur.x, cur.y, color);
		error += deltaerr;
		if (error >= 0.0)
		{
			cur.x += dir.x;
			error -= 1.0;
		}
		cur.y += dir.y;
	}
}

static void	drawray_ymajor(t_minimap *minimap, t_vec2i start, t_vec2d delta,
			int color)
{
	double	deltaerr;
	double	error;
	t_vec2i	cur;
	t_vec2i	dir;

	cur = start;
	dir.x = (delta.x < 0) ? -1 : 1;
	dir.y = (delta.y < 0) ? -1 : 1;
	error = -1.0;
	deltaerr = fabs(delta.y / delta.x);
	error += deltaerr;
	while ((frame_get_pixel(minimap->map, cur.x, cur.y) & 0x00FFFFFF) == 0)
	{
		frame_draw_pixel(minimap->overlay, cur.x, cur.y, color);
		error += deltaerr;
		if (error >= 0.0)
		{
			cur.y += dir.y;
			error -= 1.0;
		}
		cur.x += dir.x;
	}
}

void		minimap_draw_ray(t_minimap *minimap, t_vec2d pos, double direction,
			int color)
{
	t_vec2i start;
	t_vec2d delta;

	start.x = pos.x;
	start.y = pos.y;
	delta.x = cos(direction);
	delta.y = sin(direction) * -1.0f;
	if ((fabs(delta.y / delta.x) > 1.0f || delta.x == 0))
		drawray_xmajor(minimap, start, delta, color);
	else if (fabs(delta.y / delta.x) <= 1.0)
		drawray_ymajor(minimap, start, delta, color);
}

/*
** draws player direction and position on the minimap overlay, then places the
** minimap and minimap overlay on the player window at its position specified
** in the minimap struct
*/

void		minimap_render(t_rc_renderer *rend, t_minimap *minimap,
			char *window_name)
{
	void	*window;
	t_vec2i	map_pos;
	t_vec2d	player_pos;
	double	player_dir;

	window = get_rcwindow(rend, window_name);
	map_pos.x = minimap->position.x;
	map_pos.y = minimap->position.y;
	player_pos = minimap->player->position;
	player_pos.x *= minimap->scaling;
	player_pos.y *= minimap->scaling;
	player_dir = minimap->player->direction;
	frame_clear(minimap->overlay);
	minimap_draw_ray(minimap, player_pos, player_dir, 0x000000FF);
	frame_draw_pixel(minimap->overlay, player_pos.x, player_pos.y, 0x00FF0000);
	mlx_put_image_to_window(rend->mlx, window, minimap->map->id, map_pos.x,
	map_pos.y);
	mlx_put_image_to_window(rend->mlx, window, minimap->overlay->id, map_pos.x,
	map_pos.y);
}

void minimap_delete(t_rc_renderer *rend, t_minimap **minimap)
{
	frame_delete(rend, &(*minimap)->map);
	frame_delete(rend, &(*minimap)->overlay);
}
