/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 16:18:31 by cyildiri          #+#    #+#             */
/*   Updated: 2016/09/26 16:50:23 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_inti_vars(int *i, int *num, int *multiplier)
{
	*i = 0;
	*num = 0;
	*multiplier = 1;
}

static int	ft_junk_filter(char **str, int *end_index)
{
	int sign;
	int sign_found;

	sign = 1;
	sign_found = 0;
	while (!ft_isdigit((int)**str))
	{
		if (sign_found)
			return (0);
		if ((**str == ' ' || **str == '\t' || **str == '\n'
		|| **str == '\v' || **str == '\f' || **str == '\r'))
			(*str)++;
		else if (**str == '-' || **str == '+')
		{
			if (**str == '-')
				sign = -1;
			sign_found = 1;
			(*str)++;
		}
		else
			return (0);
	}
	while ((*str)[*end_index] != '\0')
		(*end_index)++;
	return (sign);
}

int			ft_atoi(const char *str)
{
	int		num;
	int		i;
	int		multiplier;
	int		sign;
	char	*ptr;

	ft_inti_vars(&i, &num, &multiplier);
	ptr = (char *)(str);
	sign = ft_junk_filter(&ptr, &i);
	while (i >= 0)
	{
		if (ft_isdigit((int)ptr[i]))
		{
			num += multiplier * (ptr[i] - '0');
			multiplier *= 10;
		}
		else
		{
			num = 0;
			multiplier = 1;
		}
		i--;
	}
	return (num * sign);
}
