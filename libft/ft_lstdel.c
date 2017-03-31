/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 11:59:25 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/12 13:51:04 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *current;
	t_list *last;

	current = *alst;
	*alst = NULL;
	if (current)
	{
		while (current->next)
		{
			last = current;
			current = current->next;
			ft_lstdelone(&last, del);
		}
		ft_lstdelone(&current, del);
	}
}
