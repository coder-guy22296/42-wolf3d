#include "wolf3d.h"

t_minimap	*new_minimap(t_rc_renderer *rend, t_frame *rc_map, t_vec2i pos,
			double scaling)
{
	t_minimap	*minimap;

	if (!(minimap = (t_minimap *)ft_memalloc(sizeof(t_minimap))))
		return (NULL);
	minimap->map = frame_resize(rend, rc_map, scaling);
	minimap->height = minimap->map->height;
	minimap->width = minimap->map->width;
	minimap->overlay = new_tframe(rend, minimap->height, minimap->width);
	minimap->scaling = scaling;
	minimap->alpha = 1.0f;
	frame_apply_alpha(minimap->map, 1.0f);
	minimap->position = pos;
	return (minimap);
}

void		minimap_add_player(t_minimap *minimap, t_player *player)
{
	minimap->player = player;
}

void		minimap_set_pos(t_minimap *minimap, t_vec2i pos)
{
	minimap->position = pos;
}

void		minimap_set_alpha(t_minimap *minimap, double transparency)
{
	frame_apply_alpha(minimap->map, transparency);
	minimap->alpha = transparency;
}

void		minimap_change_map(t_rc_renderer *rend, t_minimap *mini,
			t_frame *rc_map, double scaling)
{
	frame_delete(rend, &mini->map);
	frame_delete(rend, &mini->overlay);
	mini->map = frame_resize(rend, rc_map, scaling);
	mini->height = mini->map->height;
	mini->width = mini->map->width;
	mini->overlay = new_tframe(rend, mini->height, mini->width);
}
