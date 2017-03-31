/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 23:00:54 by cyildiri          #+#    #+#             */
/*   Updated: 2016/12/21 23:00:55 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

void	add_window(t_renderer *renderer, int width, int height, char *title)
{
	renderer->window = mlx_new_window(renderer->mlx, width, height, title);
	renderer->win_x = width;
	renderer->win_y = height;
}
