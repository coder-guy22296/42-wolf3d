/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 14:56:49 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/12 13:30:57 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *node;

	if (!(node = (t_list *)ft_memalloc(sizeof(t_list))))
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
