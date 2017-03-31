/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_renderer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:08:11 by cyildiri          #+#    #+#             */
/*   Updated: 2017/03/30 18:08:13 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdlib.h>

t_rc_renderer	*new_rc_renderer()
{
	t_rc_renderer	*rc_renderer;

	if (!(rc_renderer = (t_rc_renderer *)ft_memalloc(sizeof(t_rc_renderer))))
		return (NULL);
	if (!(rc_renderer->scene = (t_rc_scene *)ft_memalloc(sizeof(t_rc_scene))))
		return (NULL);
	rc_renderer->mlx = mlx_init();
	return (rc_renderer);
}

void			rc_renderer_delete(t_rc_renderer **rend)
{
	rc_scene_delete(*rend, &(*rend)->scene);
	windows_delete(*rend, &(*rend)->windows);
	ft_memdel(&(*rend)->mlx);
}

void			render_player_window(t_rc_renderer *rend)
{
	void		*window;
	t_frame		*cur_frame;
	t_player	*player;

	window = get_rcwindow(rend, "Player View");
	cur_frame = rend->scene->cur_frame;
	player = rend->scene->player;
	draw_floor_ceiling(cur_frame, 0x004286f4, 0x0000aa30);
	draw_walls(cur_frame, rend->scene->map, rend->scene->player);
	mlx_put_image_to_window(rend->mlx, window, cur_frame->id, 0, 0);
	minimap_render(rend, rend->scene->minimap, "Player View");
	mlx_string_put(rend->mlx, window, 0, 0, 0x33FFFFFF, "FOV:");
	mlx_string_put(rend->mlx, window, 40, 0,
		0x33FFFFFF, ft_itoa(player->fov * (180.0f / 3.14f)));
}

void			render_minimap_window( t_rc_renderer *rend)
{
	void	*window;
	t_frame	*rc_map;

	window = get_rcwindow(rend, "minimap");
	rc_map = rend->scene->minimap->map;
	if (!window)
		exit (1);
	mlx_put_image_to_window(rend->mlx, window, rc_map->id, 0, 0);
}

int				render_loop(void *param)
{
	t_rc_renderer	*rend;

	rend = (t_rc_renderer *)param;
	if (rend->scene)
	{
		render_minimap_window(rend);
		render_player_window(rend);
	}
	return (0);
}
