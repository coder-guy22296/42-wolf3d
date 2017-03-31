/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:07:40 by cyildiri          #+#    #+#             */
/*   Updated: 2017/03/30 18:07:43 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_player	*new_player(double x, double y, float direction, double fov)
{
	t_player *player;

	if (!(player = (t_player *)ft_memalloc(sizeof(t_player))))
		return (0);
	player->position.x = x;
	player->position.y = y;
	player->direction = direction;
	player->fov = fov;
	return (player);
}

void		player_translation_controls(int keycode, t_player *player)
{
	if (keycode == UP)
	{
		player->position.y -= sin(player->direction) / 4.0f;
		player->position.x += cos(player->direction) / 4.0f;
	}
	else if (keycode == DOWN)
	{
		player->position.y += sin(player->direction) / 4.0f;
		player->position.x -= cos(player->direction) / 4.0f;
	}
	else if (keycode == LEFT)
	{
		player->position.y -= sin(player->direction + 1.57f) / 4.0f;
		player->position.x += cos(player->direction + 1.57f) / 4.0f;
	}
	else if (keycode == RIGHT)
	{
		player->position.y += sin(player->direction + 1.57f) / 4.0f;
		player->position.x -= cos(player->direction + 1.57f) / 4.0f;
	}
}

void		player_rotation_controls(int keycode, t_player *player)
{
	if (keycode == A)
		player->direction += 3.14f/32.0f;
	else if (keycode == D)
		player->direction -= 3.14f/32.0f;
}

void		player_fov_controls(int keycode, t_player *player)
{
	if (keycode == W)
		player->fov += 3.14f/16.0f;
	else if (keycode == S)
		player->fov -= 3.14f/16.0f;
}
