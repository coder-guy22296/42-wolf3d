/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 23:13:55 by cyildiri          #+#    #+#             */
/*   Updated: 2016/12/21 23:13:59 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphics.h"

t_frame		new_frame(int height, int width)
{
	t_frame frame;

	ft_bzero(&frame, sizeof(frame));
	frame.height = height;
	frame.width = width;
	return (frame);
}
