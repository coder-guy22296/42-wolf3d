/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:06:20 by cyildiri          #+#    #+#             */
/*   Updated: 2017/03/30 18:06:23 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdlib.h>

int		exit_hook(t_rc_renderer *rend)
{
	rc_renderer_delete(&rend);
	exit (1);
}

int		key_hook(int keycode, void *param)
{
	t_rc_renderer	*rend;
	t_player		*player;

	rend = (t_rc_renderer *)param;
	player = rend->scene->player;
	player_translation_controls(keycode, player);
	player_rotation_controls(keycode, player);
	player_fov_controls(keycode, player);
	if (keycode == ESC)
		exit_hook(rend);
	render_loop(rend);
	return (0);
}

int		expose_hook(t_rc_renderer *rend)
{
	render_loop(rend);
	return (0);
}

void	hooks(t_rc_renderer *rend)
{
	mlx_hook(get_rcwindow(rend, "minimap"), 2, 0, key_hook, rend);
	mlx_hook(get_rcwindow(rend, "Player View"), 2, 0, key_hook, rend);
	mlx_hook(get_rcwindow(rend, "minimap"), 12, 0, expose_hook, rend);
	mlx_hook(get_rcwindow(rend, "Player View"), 12, 0, expose_hook, rend);
	mlx_hook(get_rcwindow(rend, "minimap"), 17, 0, exit_hook, rend);
	mlx_hook(get_rcwindow(rend, "Player View"), 17, 0, exit_hook, rend);
	mlx_loop(rend->mlx);
}
