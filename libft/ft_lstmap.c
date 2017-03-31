/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 12:31:35 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/12 14:49:19 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *current;
	t_list *output;

	output = NULL;
	current = lst;
	if (current)
	{
		while (current->next)
		{
			ft_lstaddend(&output, f(current));
			current = current->next;
		}
		ft_lstaddend(&output, f(current));
	}
	else
		output = NULL;
	return (output);
}
