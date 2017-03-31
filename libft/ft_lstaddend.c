/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 14:46:14 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/12 14:59:30 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alist, t_list *new)
{
	t_list *cur;

	cur = *alist;
	if (cur)
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	else
		*alist = new;
}
