/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 22:59:13 by cyildiri          #+#    #+#             */
/*   Updated: 2017/03/29 22:59:17 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

typedef struct	s_vec2f
{
	float		x;
	float		y;
}				t_vec2f;

typedef struct	s_vec2d
{
	double		x;
	double		y;
}				t_vec2d;

typedef struct	s_player
{
	t_vec2d		position;
	double		direction;
	double		fov;

}				t_player;

typedef struct	s_minimap
{
	t_player	*player;
	t_frame		*map;
	t_frame		*overlay;
	double		alpha;
	t_vec2i		position;
	int			height;
	int			width;
	double		scaling;
}				t_minimap;

typedef struct	s_rc_scene
{
	t_frame		*map;
	t_minimap	*minimap;
	t_player	*player;
	t_frame		*cur_frame;
}				t_rc_scene;

typedef struct	s_rc_renderer
{
	void		*mlx;
	t_lmap		*windows;
	int			win_x;
	int			win_y;
	t_rc_scene	*scene;
}				t_rc_renderer;

typedef struct	s_ray
{
	t_vec2d		position;
	double		direction;
	t_vec2d		cur;
	int			xdir;
	int			ydir;
	double		x_step;
	double		y_step;
}				t_ray;

#endif
