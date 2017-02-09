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
#include <fcntl.h>
#include <stdlib.h>
#include "math.h"

typedef struct	s_vec2f
{
	float		x;
	float		y;
}				t_vec2f;
typedef struct	s_vec2d
{
    double  	x;
    double		y;
}				t_vec2d;
typedef struct	s_player
{
	t_vec2i		position;
	float		direction;
	float		fov;

}				t_player;

typedef struct	s_rc_scene
{
	t_frame		*map;
	t_player	*player;
	t_frame		*cur_frame;
}				t_rc_scene;

typedef struct	s_rc_renderer
{
    void		*mlx;
    void		*window;
    int			win_x;
    int			win_y;
    t_rc_scene	*scene;

    void		(*render)(struct s_rc_renderer *renderer);
}				t_rc_renderer;

t_rc_renderer	*new_rc_renderer(void (*render)(t_rc_renderer *))
{
    t_rc_renderer	*rc_renderer;

    if (!(rc_renderer = (t_rc_renderer *)ft_memalloc(sizeof(t_rc_renderer))))
        return (NULL);
    rc_renderer->mlx = mlx_init();
    rc_renderer->render = render;
    if (!(rc_renderer->scene = (t_rc_scene *)ft_memalloc(sizeof(t_rc_scene))))
        return (0);
    return (rc_renderer);
}

void	add_rcwindow(t_rc_renderer *renderer, int width, int height, char *title)
{
    renderer->window = mlx_new_window(renderer->mlx, width, height, title);
    renderer->win_x = width;
    renderer->win_y = height;
}

void del_intArr(int **arr, int rows)
{
    int i;

    i = 0;
    while (i < rows)
    {
        ft_memdel((void *)&(arr[i]));
        i++;
    }
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

/*
**	allocates and zeros a 2d array of a specified element
*/

void		**new_2darray(int rows, int columns, size_t element_size)
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

t_frame		*new_tframe(t_rc_renderer *renderer, int height, int width)
{
    t_frame *frame;

    if(!(frame = (t_frame *)ft_memalloc(sizeof(t_frame))))
        return (0);
    frame->id = mlx_new_image(renderer->mlx, width, height);
    frame->image = mlx_get_data_addr(
            frame->id,
            &frame->color_depth,
            &frame->line_size,
            &frame->endien);
    frame->height = height;
    frame->width = width;
    return (frame);
}

int draw_pixel(t_frame *frame, int x, int y, int color)
{
    unsigned int	*image;
    int				pos;

    image = (unsigned int *)frame->image;
    if (x < 0 || x >= frame->width
        || y < 0 || y >= frame->height)
    {
        return (1);
    }
    pos = x + (y * frame->line_size / 4);
    image[pos] = (unsigned int)color;
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
            draw_pixel(frame, x + j, y + i, 0x00FFFFFF);
            j++;
        }
        i++;
    }
}

int **load_map(char *filename, t_vec2i *row_col)
{
	t_list		*lines;
	int			**array2d;
	int			file;

	if ((file = open(filename, O_RDONLY)) == -1)
	{
		ft_putstr("bad file!\n");
		exit(1);
	}
    lines = NULL;
    (*row_col).y = load_into_list(file, &lines, &(*row_col).x);
	array2d = (int **)new_2darray((*row_col).y, (*row_col).x, sizeof(int));
	convert_list2array(lines, array2d, (*row_col).y, (*row_col).x);

    return(array2d);
}


t_frame *construct_map(t_rc_renderer *renderer, int **array2d, int block_size, t_vec2i *row_col)
{
    t_frame *frame;
    int i;
    int j;

    //malloc frame
    frame = new_tframe(renderer, renderer->win_y, renderer->win_x);
    i = 0;
    while (i < row_col->y)
    {
        j = 0;
        while (j < row_col->x)
        {
            if (array2d[i][j] == 1)
                draw_square(frame, j * block_size, i * block_size, block_size);
            j++;
        }
        i++;
    }
    return (frame);
}

void	render(/* t_rc_renderer *renderer */)
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


int			render_loop(void *param)
{
    t_rc_renderer	*renderer;

    renderer = (t_rc_renderer *)param;
    if (renderer->scene)
        renderer->render(renderer);
    return (0);
}

t_player *new_player(int x, int y, float direction, int fov)
{
    t_player *player;

    if (!(player = (t_player *)ft_memalloc(sizeof(t_player))))
        return (0);
    player->position.x = x;
    player->position.y = y;
    player->direction = direction;
    player->fov = fov;
    return (player);
}

int		key_pressed(int keycode, void *param)
{
    t_rc_renderer	*renderer;

    renderer = (t_rc_renderer *)param;
    if (keycode == UP)
        renderer->scene->player->position.y -= 1;
    else if (keycode == DOWN)
        renderer->scene->player->position.y += 1;
    else if (keycode == LEFT)
        renderer->scene->player->position.x -= 1;
    else if (keycode == RIGHT)
        renderer->scene->player->position.x += 1;
    else if (keycode == A)
        renderer->scene->player->direction += 3.14/16;
    else if (keycode == D)
        renderer->scene->player->direction -= 3.14/16;
    if (keycode == ESC)
        exit(1);
    return (0);
}
static void		drawray_xmajor(t_rc_renderer *renderer, t_vec2i start, t_vec2d delta)
{
    double	deltaerr;
    double	error;
    int     length = 0;
    t_vec2i cur;
    t_vec2i dir;

    cur = start;
    dir.x = (delta.x < 0) ? -1 : 1;
    dir.y = (delta.y < 0) ? -1 : 1;
    error = -1.0;
    deltaerr = fabs(delta.x / delta.y);
    while (length < 15)
    {
        if (cur.y == start.y)
            error += deltaerr;
        mlx_pixel_put(renderer->mlx, renderer->window, cur.x, cur.y, 0x000000FF);
        error += deltaerr;
        if (error >= 0.0)
        {
            cur.x += dir.x;
            error -= 1.0;
        }
        cur.y += dir.y;
        length++;
    }
}

static void		drawray_ymajor(t_rc_renderer *renderer, t_vec2i start, t_vec2d delta)
{
    double	deltaerr;
    double	error;
    int     length = 0;
    t_vec2i cur;
    t_vec2i dir;

    cur = start;
    dir.x = (delta.x < 0) ? -1 : 1;
    dir.y = (delta.y < 0) ? -1 : 1;
    error = -1.0;
    deltaerr = fabs(delta.y / delta.x);
    error += deltaerr;
    while (length < 15)
    {
        mlx_pixel_put(renderer->mlx, renderer->window, cur.x, cur.y, 0x000000FF);
        error += deltaerr;
        if (error >= 0.0)
        {
            cur.y += dir.y;
            error -= 1.0;
        }
        cur.x += dir.x;
        length++;
    }
}
void draw_player_ray(t_rc_renderer *renderer)
{
    t_vec2i start;
    t_player *player;
    t_vec2d delta;


    player = renderer->scene->player;
    start.x = player->position.x;
    start.y = player->position.y;
    delta.x = cos(player->direction);
    delta.y = sin(player->direction);

    if ((fabs(delta.y / delta.x) > 1.0f || delta.x == 0))
        drawray_xmajor(renderer, start, delta);
    else if (fabs(delta.y / delta.x) <= 1.0)
        drawray_ymajor(renderer, start, delta);


}


void	render_map( t_rc_renderer *renderer)
{
    mlx_clear_window(renderer->mlx, renderer->window);
    //display map image for testing purposes
    mlx_put_image_to_window(renderer->mlx, renderer->window, renderer->scene->map->id, 0, 0);

    draw_player_ray(renderer);

    mlx_pixel_put(renderer->mlx, renderer->window, renderer->scene->player->position.x,
                  renderer->scene->player->position.y,
                  0x00FF0000);
}

int main(int argc, char **argv)
{
    int			    **array2d;
	t_rc_renderer	*rc_renderer;
    t_vec2i         *row_col;

    if (argc != 2)
    {
        //usage
        return (0);
    }
    array2d = NULL;
    row_col = new_vec2i(0,0);

    //initalize ray caster
    rc_renderer = new_rc_renderer(render_map);

    //add window
    add_rcwindow(rc_renderer, 1000, 1000, "cyildiri's wolf3d");

    //load map to a 2d array
    array2d = load_map(argv[1], row_col);

    //construct an image map that will be used for casting rays
    rc_renderer->scene->map = construct_map(rc_renderer, array2d, 15, row_col);

    //free the memory used for the 2d array
    del_intArr(array2d, row_col->y);

    //add a player
    rc_renderer->scene->player = new_player(50, 50, 0, 60);

    //display map image for testing purposes
    mlx_put_image_to_window(rc_renderer->mlx, rc_renderer->window, rc_renderer->scene->map->id, 0, 0);

    mlx_pixel_put(rc_renderer->mlx, rc_renderer->window, rc_renderer->scene->player->position.x,
                  rc_renderer->scene->player->position.y,
                  0x00FF0000);
    draw_player_ray(rc_renderer);

    mlx_hook(rc_renderer->window, 2, 0, key_pressed, rc_renderer);

    mlx_loop_hook(rc_renderer->mlx, render_loop, rc_renderer);
    // run the mlx loop
    mlx_loop(rc_renderer->mlx);

	//clean up

	return (0);
}