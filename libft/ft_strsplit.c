/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 16:56:23 by cyildiri          #+#    #+#             */
/*   Updated: 2016/10/05 17:25:11 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**ft_alloc_word_mem(int words, char const *s, char c, char **new)
{
	int		word_start;
	char	lastchar;
	int		index;
	int		word;

	word_start = 0;
	lastchar = c;
	index = 0;
	word = 0;
	while (word < words)
	{
		if (lastchar == c)
			word_start = index;
		else if (s[index] == c || s[index] == '\0')
		{
			if (!(new[word++] = ft_strnew(index - word_start)))
			{
				ft_stradel(&new);
				return (NULL);
			}
		}
		lastchar = s[index++];
	}
	return (new);
}

static char	**ft_copy_words(int words, char const *s, char c, char **new)
{
	char	lastchar;
	int		index;
	int		word;
	int		i;

	lastchar = c;
	index = 0;
	word = 0;
	i = 0;
	while (word < words)
	{
		if ((s[index] == c || s[index] == '\0') && lastchar != c)
		{
			i = 0;
			word++;
		}
		if (s[index] != c && s[index] != '\0')
			new[word][i++] = (char)s[index];
		lastchar = s[index++];
	}
	new[words] = NULL;
	return (new);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str_arr;
	int		words;

	if (s == NULL)
		return (NULL);
	words = ft_cntwords(s, c);
	if (!(str_arr = (char **)ft_memalloc(sizeof(char *) * (words + 1))))
		return (NULL);
	if (!(str_arr = ft_alloc_word_mem(words, s, c, str_arr)))
		return (NULL);
	str_arr = ft_copy_words(words, s, c, str_arr);
	return (str_arr);
}
