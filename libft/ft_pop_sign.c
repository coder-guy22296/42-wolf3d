/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 16:18:45 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/09 16:19:39 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_pop_sign(int n, int *sign)
{
	unsigned int buff;

	*sign = 0;
	if (n < 0)
	{
		*sign = 1;
		buff = (unsigned int)(n * -1);
	}
	else
		buff = (unsigned int)n;
	return (buff);
}
