/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 21:09:52 by cyildiri          #+#    #+#             */
/*   Updated: 2017/03/29 22:58:38 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdlib.h>
#include <unistd.h>

t_frame	*construct_map(t_rc_renderer *rend, int **array2d, int block_size,
t_vec2i *row_col)
{
	t_frame	*frame;
	int		i;
	int		j;

	frame = new_tframe(rend, row_col->y * block_size, row_col->x * block_size);
	i = 0;
	while (i < row_col->y)
	{
		j = 0;
		while (j < row_col->x)
		{
			if (array2d[i][j] == 1)
			{
				frame_draw_square(frame, j * block_size, i * block_size,
				block_size);
			}
			j++;
		}
		i++;
	}
	return (frame);
}

void	rc_scene_delete(t_rc_renderer *rend, t_rc_scene **scene)
{
	frame_delete(rend, &(*scene)->map);
	frame_delete(rend, &(*scene)->cur_frame);
	minimap_delete(rend, &(*scene)->minimap);
	ft_memdel((void **)&(*scene)->player);
	ft_memdel((void **)scene);
}

void	setup_minimap(t_rc_renderer *rend, t_minimap **minimap)
{
	*minimap = new_minimap(rend, rend->scene->map, vec2i(800, 800), 6.0);
	minimap_add_player(*minimap, rend->scene->player);
	minimap_set_alpha(*minimap, 1.0);
	add_rcwindow(rend, (*minimap)->height, (*minimap)->width, "minimap");
}

int		main(int argc, char **argv)
{
	int				**array2d;
	t_rc_renderer	*rend;
	t_vec2i			*row_col;
	int				block_size;

	block_size = 1;
	if (argc != 2)
	{
		ft_putstr("usage: ./wolf3d <wolf file>\n");
		return (0);
	}
	array2d = NULL;
	row_col = new_vec2i(0,0);
	rend = new_rc_renderer();
	array2d = load_map(argv[1], row_col);
	add_rcwindow(rend, 1000, 1000, "Player View");
	rend->scene->map = construct_map(rend, array2d, block_size, row_col);
	del_intArr(array2d, row_col->y);
	ft_memdel((void *)&row_col);
	rend->scene->player = new_player(1.5, 1.5, 2.3561944902f, 1.02548);
	rend->scene->cur_frame = new_tframe(rend, rend->win_y, rend->win_x);
	setup_minimap(rend, &rend->scene->minimap);
	hooks(rend);
	exit_hook(rend);
	return (0);
}
