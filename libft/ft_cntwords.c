/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntwords.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 21:11:30 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/05 11:42:26 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_cntwords(char const *str, char delim)
{
	char	lastchar;
	int		index;
	int		words;

	words = 0;
	lastchar = delim;
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == delim)
			if (lastchar != delim)
				words++;
		lastchar = str[index];
		index++;
	}
	if (lastchar != delim)
		words++;
	return (words);
}
