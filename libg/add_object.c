/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 15:41:48 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/26 15:41:49 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

void	add_object(t_scene *scene, t_3d_object *obj)
{
	ft_lstadd(&(scene->objects), ft_lstnew(obj, sizeof(t_3d_object)));
}
