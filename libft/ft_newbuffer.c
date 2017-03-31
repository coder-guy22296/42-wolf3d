/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newbuffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 18:04:30 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/29 18:15:39 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_buff	*ft_newbuffer(int buffer_len, size_t elem_size)
{
	t_buff *buff;

	if (!(buff = (t_buff *)ft_memalloc(sizeof(t_buff))))
		return (NULL);
	if (!(buff->buffer = ft_memalloc(elem_size * buffer_len)))
		return (NULL);
	buff->buffer_len = buffer_len;
	buff->buf_util = 0;
	return (buff);
}
