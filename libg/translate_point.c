/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:48:57 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/23 17:48:58 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

t_vec3fc	translate_point(t_vec3fc original, t_vec3fc translation)
{
	t_vec3fc translated_point;

	translated_point.x = original.x + translation.x;
	translated_point.y = original.y + translation.y;
	translated_point.z = original.z + translation.z;
	translated_point.color = original.color;
	return (translated_point);
}
