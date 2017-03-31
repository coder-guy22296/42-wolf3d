/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:06:37 by cyildiri          #+#    #+#             */
/*   Updated: 2017/03/30 18:06:40 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	distance(t_vec2d point_a, t_vec2d point_b)
{
	double	a_squared;
	double	b_squared;

	a_squared = pow(point_a.x - point_b.x, 2);
	b_squared = pow(point_a.y - point_b.y, 2);
	return ( sqrt(a_squared + b_squared) );
}

int		apply_alpha(int original_color, double alpha)
{
	int	solid_color;
	int	alpha_color;

	solid_color = original_color & 0x00FFFFFF;
	alpha_color = solid_color | ((int)((1.00f - alpha) * 255)) << 24;
	return (alpha_color);
}

void	del_intArr(int **arr, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		ft_memdel((void *)&(arr[i]));
		i++;
	}
}
