/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 19:45:29 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/09 19:47:19 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_digits(int n)
{
	int				i;
	unsigned int	cur;
	int				sign;

	i = 0;
	cur = ft_pop_sign(n, &sign);
	if (n == 0)
		return (1);
	while (cur >= 1)
	{
		cur /= 10;
		i++;
	}
	return (i);
}
