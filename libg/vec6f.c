/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec6f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 21:21:16 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/21 21:33:35 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

t_vec6f	*new_vec6f(t_vec3fc pos, t_vec3fc rot)
{
	t_vec6f *pos_rot;

	if (!(pos_rot = (t_vec6f *)ft_memalloc(sizeof(t_vec6f))))
		return (NULL);
	pos_rot->position = pos;
	pos_rot->rotation = rot;
	return (pos_rot);
}

t_vec6f	vec6f(t_vec3fc pos, t_vec3fc rot)
{
	t_vec6f pos_rot;

	pos_rot.position = pos;
	pos_rot.rotation = rot;
	return (pos_rot);
}
