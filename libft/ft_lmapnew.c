/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lmapnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 12:15:03 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/26 12:41:04 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lmap	*ft_lmapnew(void const *key, size_t key_size, void const *content,
					size_t content_size)
{
	t_lmap *node;

	if (!(node = (t_lmap *)ft_memalloc(sizeof(t_lmap))))
		return (NULL);
	if (key && (node->key = ft_memalloc(key_size)))
	{
		node->key_size = key_size;
		ft_memcpy(node->key, key, key_size);
	}
	else
		return (NULL);
	if (content)
	{
		node->content_size = content_size;
		if (!(node->content = ft_memalloc(content_size)))
			return (NULL);
		ft_memcpy(node->content, content, content_size);
	}
	else
	{
		node->content_size = 0;
		node->content = NULL;
	}
	node->next = NULL;
	return (node);
}
