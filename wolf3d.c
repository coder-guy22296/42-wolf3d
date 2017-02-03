/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 21:09:52 by cyildiri          #+#    #+#             */
/*   Updated: 2017/01/31 21:09:54 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "wolf3d.h"
#include "libgraphics.h"

typedef struct	s_vec2f
{
	float		x;
	float		y;
}				t_vec2f;

typedef struct	s_player
{
	t_vec2f		position;
	float		direction;
	float		fov;

}				t_player;

typedef struct	s_2d_scene
{
	t_frame		map;
	t_player	*player;
	t_frame		cur_frame;
}				t_scene;

void	render(/* scene */)
{
	//
	//	<< loop start
	//		cast rays (player, map)
	//		calculate slice height
	//		draw slice to frame
	//	<< loop end
	// display frame
	// destroy frame
}

/*
**	Load an fdf file into a linked list of arrays of strings
*/

int			load_into_list(int fd, t_list **lines, int *max_column_cnt)
{
	char		*line;
	int			line_cnt;
	int			col_cnt;
	char		**column_arr;

	line_cnt = 0;
	*max_column_cnt = -99;
	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		column_arr = ft_strsplit(line, ' ');
		col_cnt = ft_cntwords(line, ' ');
		*max_column_cnt =
				(col_cnt > *max_column_cnt) ? col_cnt : *max_column_cnt;
		ft_lstadd(lines, ft_lstnew((void *)column_arr,
								   sizeof(char *) * (col_cnt + 1)));
		ft_memdel((void **)&line);
		line_cnt++;
	}
	return (line_cnt);
}

/*
**	Converts a linked list of arrays of strings into a 2d array of integers
*/

void		convert_list2array(t_list *lines, int **arr2d,
							   int rows, int columns)
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

int draw_pixel(t_frame *frame, int x, int y, int color)
{
    unsigned int	*image;
    int				pos;

    image = (unsigned int *)frame->image;
    if (place_me.x < 0 || place_me.x >= scene->cur_frame.width
        || place_me.y < 0 || place_me.y >= scene->cur_frame.height)
    {
        return (1);
    }
    pos = place_me.x + (place_me.y * frame->line_size / 4);
    image[pos] = (unsigned int)place_me.color;
    return (0);
}

void draw_square(t_frame *frame, int x, int y, int size)
{
    int i;
    int j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            draw_pixel(frame, pos.x + j, pos.y + i, 0x00FFFFFF);
            j++;
        }
        i++;
    }
}

int **load_map(char *filename)
{
	t_list		*lines;
	int			**array2d;
	t_vec2i		row_col;
	int			file;

	if ((file = open(filename, O_RDONLY)) == -1)
	{
		ft_putstr("bad file!\n");
		exit(1);
	}
	row_col.y = load_into_list(file, &lines, &row_col.x);
	array2d = (int **)new_2darray(row_col.y, row_col.x, sizeof(int));
	convert_list2array(lines, array2d, row_col.y, row_col.x);

    return(array2d);
}

t_frame		new_frame(t_renderer renderer, int height, int width)
{
    t_frame frame;

    ft_bzero(&frame, sizeof(frame));
    frame.id = mlx_new_image(renderer->mlx, width, height);
    renderer->scene->cur_frame.image = mlx_get_data_addr(
            &frame.id,
            &frame.color_depth,
            &frame.line_size,
            &frame.endien);
    frame.height = height;
    frame.width = width;
    return (frame);
}

t_frame *construct_map(t_renderer renderer, int **array2d, int block_size)
{
    t_frame *frame;
    int i;
    int j;

    //malloc frame
    frame = new_frame(renderer, height, width);

    i = 0;
    while (i < row_col.y)
    {
        j = 0;
        while (j < row_col.x)
        {
            if (array2d[i][j] == 1)
                draw_square(frame, j * block_size, i * block_size, block_size);
            j++;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    int			**array2d;
    t_2d_scene  scene2d;
	t_renderer	wolf3d_renderer;

	add_window(&wolf3d_renderer, 1000, 1000, "cyildiri's wolf3d");
    array2d = load_map(argv[1]);
    scene2d.map = construct_map(&wolf3d_renderer, array2d, 50);


	// open window

	// load map into image
	// setup hooks

	//clean up


	return (0);
}