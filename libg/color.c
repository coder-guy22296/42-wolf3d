/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 10:12:09 by cyildiri          #+#    #+#             */
/*   Updated: 2017/01/06 10:12:11 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"
#include "stdlib.h"

static int	extract_byte(int target, int bits_from_right)
{
	return ((target & (255 << bits_from_right)) >> bits_from_right);
}

t_color		color(int color32)
{
	t_color	str_color;

	str_color.red = extract_byte(color32, RED);
	str_color.green = extract_byte(color32, GREEN);
	str_color.blue = extract_byte(color32, BLUE);
	str_color.alpha = extract_byte(color32, ALPHA);
	return (str_color);
}

int			blend(int color_a, int color_b, float percentage)
{
	t_color	str_color1;
	t_color	str_color2;
	t_color	delta;
	int		blend;

	str_color1 = color(color_a);
	str_color2 = color(color_b);
	if (color_a == color_b || percentage < 0.000001)
		return (color_a);
	delta.red = (str_color2.red - str_color1.red);
	delta.green = (str_color2.green - str_color1.green);
	delta.blue = (str_color2.blue - str_color1.blue);
	blend = (((int)(str_color1.red + (delta.red * percentage))) << 16)
			| (((int)(str_color1.green + (delta.green * percentage))) << 8)
			| ((int)(str_color1.blue + (delta.blue * percentage)));
	return (blend);
}
