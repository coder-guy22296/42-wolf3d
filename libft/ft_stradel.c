/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 20:28:36 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/05 10:26:29 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <strings.h>

void	ft_stradel(char ***arr)
{
	int i;

	i = 0;
	while (*arr[i] != '\0')
	{
		if (*arr[i])
		{
			free(*arr[i]);
			*arr[i] = NULL;
		}
		i++;
	}
	free(*arr[i]);
	*arr[i] = NULL;
	free(**arr);
	**arr = NULL;
}
