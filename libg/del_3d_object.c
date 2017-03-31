/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_3d_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 13:02:58 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/27 13:02:59 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

void	del_3d_object(t_3d_object *obj)
{
	ft_memdel((void **)&(obj->faces_arr));
	ft_memdel((void **)&(obj->vertex_ind));
	ft_memdel((void **)&(obj->vertices));
	ft_memdel((void **)&obj);
}
