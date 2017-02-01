/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 21:09:52 by cyildiri          #+#    #+#             */
/*   Updated: 2017/01/31 21:09:54 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "wolf3d.h"

typedef struct	s_vec2f
{
	float		x;
	float		y;
}				t_vec2f;

typedef struct	s_player
{
	t_vec2f		position;
	float		direction;
	float		fov;

}				t_player;

typedef struct	s_2d_scene
{
	t_frame		map;
	t_player	*player;
	t_frame		cur_frame;
}				t_scene;

void	render(/* scene */)
{
	//
	//	<< loop start
	//		cast rays (player, map)
	//		calculate slice height
	//		draw slice to frame
	//	<< loop end
	// display frame
	// destroy frame
}

int main()
{
	// open window

	// load map into image
	// setup hooks

	//clean up


	return (0);
}