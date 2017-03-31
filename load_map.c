/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:06:54 by cyildiri          #+#    #+#             */
/*   Updated: 2017/03/30 18:06:57 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/*
**	Load an fdf file into a linked list of arrays of strings
*/

int		load_into_list(int fd, t_list **lines, int *max_column_cnt)
{
	char	*line;
	int		line_cnt;
	int		col_cnt;
	char	**column_arr;

	line_cnt = 0;
	*max_column_cnt = -99;
	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		column_arr = ft_strsplit(line, ' ');
		col_cnt = ft_cntwords(line, ' ');
		*max_column_cnt =
			(col_cnt > *max_column_cnt) ? col_cnt : *max_column_cnt;
		ft_lstaddend(lines, ft_lstnew((void *)column_arr,
			sizeof(char *) * (col_cnt + 1)));
		ft_memdel((void **)&line);
		line_cnt++;
	}
	return (line_cnt);
}

/*
**	Converts a linked list of arrays of strings into a 2d array of integers
*/

void	convert_list2array(t_list *lines, int **arr2d, int rows,
		int columns)
{
	t_list	*tmp;
	int		valid_col;
	int		row;
	int		col;

	row = 0;
	while (lines != NULL && row < rows)
	{
		tmp = lines->next;
		col = 0;
		valid_col = (((char **)lines->content)[col] == 0) ? 0 : 1;
		while (col < columns)
		{
			if (valid_col)
			{
				valid_col = (((char **)lines->content)[col + 1] == 0) ? 0 : 1;
				arr2d[row][col] = ft_atoi(((char **)lines->content)[col]);
			}
			else
				arr2d[row][col] = -2147483648;
			col++;
		}
		lines = tmp;
		row++;
	}
}

/*
**	allocates and zeros a 2d array of a specified element
*/

void	**new_2darray(int rows, int columns, size_t element_size)
{
	void	**array_2d;
	int		row;

	if (!(array_2d = ft_memalloc(sizeof(void *) * (rows + 1))))
		return (NULL);
	row = 0;
	while (row < rows)
	{
		array_2d[row] = ft_memalloc(element_size * (columns + 1));
		row++;
	}
	return (array_2d);
}

int		file_is_valid(char *filename)
{
	int		file;
	char	*line;
	char	*str;
	char	*tmp;

	if ((file = open(filename, O_RDONLY)) == -1)
		return (0);
	str = "\0";
	while (get_next_line(file, &line) == 1)
	{
		tmp = str;
		str = ft_strjoin(tmp, line);
		if (tmp[0])
			ft_strdel(&tmp);
		ft_memdel((void **)&line);
	}
	close(file);
	if (ft_strchr(str, '0') && ft_strchr(str, '1') && ft_strchr(str, ' '))
		return (1);
	return (0);
}

int		**load_map(char *filename, t_vec2i *row_col)
{
	t_list	*lines;
	int		**array2d;
	int		file;

	lines = NULL;
	if (file_is_valid(filename))
	{
		file = open(filename, O_RDONLY);
		(*row_col).y = load_into_list(file, &lines, &(*row_col).x);
		close(file);
		array2d = (int **)new_2darray((*row_col).y, (*row_col).x, sizeof(int));
		convert_list2array(lines, array2d, (*row_col).y, (*row_col).x);
		return(array2d);
	}
	ft_putstr("bad file!\n");
	exit (1);
}
