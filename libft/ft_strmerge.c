/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 14:02:17 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/27 14:02:20 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	this function appends add_str to the main_str and frees the original strings
*/

char	*ft_strmerge(char **main_str, char *add_str)
{
	char *new;

	if (!(new = ft_strjoin(*main_str, add_str)))
		return (NULL);
	ft_strdel(main_str);
	ft_strdel(&add_str);
	*main_str = new;
	return (*main_str);
}
