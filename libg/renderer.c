/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 22:37:48 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/21 22:44:20 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

t_renderer	*new_renderer(void (*render)(t_renderer *, t_scene))
{
	t_renderer	*renderer3d;

	if (!(renderer3d = (t_renderer *)ft_memalloc(sizeof(t_renderer))))
		return (NULL);
	renderer3d->mlx = mlx_init();
	renderer3d->render = render;
	renderer3d->last_click.x = -99;
	renderer3d->last_click.y = -99;
	return (renderer3d);
}

t_renderer	renderer(void (*render)(t_renderer *, t_scene))
{
	t_renderer	renderer3d;

	renderer3d.mlx = mlx_init();
	renderer3d.render = render;
	return (renderer3d);
}
