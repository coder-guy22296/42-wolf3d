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
#include <stdio.h>

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
	t_vec2d		position;
	double		direction;
	double		fov;

}				t_player;

typedef struct	s_rc_scene
{
	t_frame		*map;
	t_frame		*minimap;
	t_player	*player;
	t_frame		*cur_frame;
}				t_rc_scene;

typedef struct	s_rc_renderer
{
	void		*mlx;
	t_lmap      *windows;
	int			win_x;
	int			win_y;
	t_rc_scene	*scene;

}				t_rc_renderer;

t_rc_renderer	*new_rc_renderer()
{
	t_rc_renderer	*rc_renderer;

	if (!(rc_renderer = (t_rc_renderer *)ft_memalloc(sizeof(t_rc_renderer))))
		return (NULL);
	rc_renderer->mlx = mlx_init();
	if (!(rc_renderer->scene = (t_rc_scene *)ft_memalloc(sizeof(t_rc_scene))))
		return (0);
	return (rc_renderer);
}

void	add_rcwindow(t_rc_renderer *renderer, int width, int height, char *title)
{
	t_lmap *to_add;
	void    *new_window;

	new_window = mlx_new_window(renderer->mlx, width, height, title);
	to_add = ft_lmapnew(title, sizeof(title), &new_window, sizeof(new_window));
	//printf("%p\n", new_window);
	ft_lmapadd(&renderer->windows, to_add);
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

int get_pixel(t_frame *frame, int x, int y)
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
	return (image[pos]);
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

void clear_frame(t_frame *frame)
{
	int i;
	int j;

	i = 0;
	while (i < frame->height)
	{
		j = 0;
		while (j < frame->width)
		{
			draw_pixel(frame, j, i, 0);
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

	//malloc frames
	renderer->scene->minimap = new_tframe(renderer, renderer->win_y, renderer->win_x);
	clear_frame(renderer->scene->minimap);
	frame = new_tframe(renderer, renderer->win_y, renderer->win_x);
	i = 0;
	while (i < row_col->y)
	{
		j = 0;
		while (j < row_col->x)
		{
			if (array2d[i][j] == 1)
            {
                draw_square(frame, j * block_size, i * block_size, block_size);
                draw_square(renderer->scene->minimap, j * block_size * 6, i * block_size * 6, block_size * 6);

            }
			j++;
		}
		i++;
	}
	return (frame);
}

t_player *new_player(int x, int y, float direction, double fov)
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


static void		drawray_xmajor(t_rc_renderer *renderer, char *window_name, t_vec2i start, t_vec2d delta)
{
	double	deltaerr;
	double	error;
	int     length = 0;
	t_vec2i cur;
	t_vec2i dir;
	void *window;

	cur = start;
	window = *((void **)ft_lmapget(renderer->windows, window_name)->content);
	dir.x = (delta.x < 0) ? -1 : 1;
	dir.y = (delta.y < 0) ? -1 : 1;
	error = -1.0;
	deltaerr = fabs(delta.x / delta.y);
	while (1)
	{
		if (get_pixel(renderer->scene->map, cur.x, cur.y) != 0)
			break;
		if (cur.y == start.y)
			error += deltaerr;
		mlx_pixel_put(renderer->mlx, window, cur.x, cur.y, 0x000000FF);
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

static void		drawray_ymajor(t_rc_renderer *renderer, char *window_name, t_vec2i start, t_vec2d delta)
{
	double	deltaerr;
	double	error;
	t_vec2i cur;
	t_vec2i dir;
	void *window;

	cur = start;
	window = *((void **)ft_lmapget(renderer->windows, window_name)->content);
	dir.x = (delta.x < 0) ? -1 : 1;
	dir.y = (delta.y < 0) ? -1 : 1;
	error = -1.0;
	deltaerr = fabs(delta.y / delta.x);
	error += deltaerr;
	while (1)
	{
		if (get_pixel(renderer->scene->map, cur.x, cur.y) != 0)
			break;
		mlx_pixel_put(renderer->mlx, window, cur.x, cur.y, 0x000000FF);
		error += deltaerr;
		if (error >= 0.0)
		{
			cur.y += dir.y;
			error -= 1.0;
		}
		cur.x += dir.x;
	}
}
void draw_player_ray(t_rc_renderer *renderer, char *window_name)
{
	t_vec2i start;
	t_player *player;
	t_vec2d delta;


	player = renderer->scene->player;
	start.x = player->position.x;
	start.y = player->position.y;
	delta.x = cos(player->direction);
	delta.y = sin(player->direction) * -1.0f;

	if ((fabs(delta.y / delta.x) > 1.0f || delta.x == 0))
		drawray_xmajor(renderer, window_name, start, delta);
	else if (fabs(delta.y / delta.x) <= 1.0)
		drawray_ymajor(renderer, window_name, start, delta);


}

//static double		castray_xmajor(t_frame *map, t_vec2i start, t_vec2d delta)
//{
//	double	deltaerr;
//	double	error;
//	t_vec2i cur;
//	t_vec2i dir;
//
//	cur = start;
//	dir.x = (delta.x < 0) ? -1 : 1;
//	dir.y = (delta.y < 0) ? -1 : 1;
//	error = -1.0;
//	deltaerr = fabs(delta.x / delta.y);
//	while (1)
//	{
//		//if (get_pixel(map, cur.x, cur.y) == 0x00FFFFFF)
//		//    break;
//		if (get_pixel(map, cur.x, cur.y)  != 0x000000FF)
//			draw_pixel(map, cur.x, cur.y, 0x0000FF00);
//		if (cur.y == start.y)
//			error += deltaerr;
//		error += deltaerr;
//		if (error >= 0.0)
//		{
//			cur.x += dir.x;
//			error -= 1.0;
//		}
//		/*if (get_pixel(map, cur.x, cur.y) == 0x00FFFFFF)
//		{
//			printf("ax\n");
//			return (((double)cur.x - (double)start.x)/delta.x);
//		}*/
//		cur.y += dir.y;
//		if (get_pixel(map, cur.x, cur.y) == 0x00FFFFFF) {
//			printf("bx\n");
//			return (((double) cur.y - (double) start.y) / delta.y);
//		}
//	}
//	printf("impact: (%d,%d)\n", cur.x, cur.y);
//	//return (((double)cur.y - (double)start.y)/delta.y);
//}
//
//static double		castray_ymajor(t_frame *map, t_vec2i start, t_vec2d delta)
//{
//	double	deltaerr;
//	double	error;
//	t_vec2i cur;
//	t_vec2i dir;
//
//	cur = start;
//	dir.x = (delta.x < 0) ? -1 : 1;
//	dir.y = (delta.y < 0) ? -1 : 1;
//	error = -1.0;
//	deltaerr = fabs(delta.y / delta.x);
//	error += deltaerr;
//	while (1)
//	{
//		//if (get_pixel(map, cur.x, cur.y)  == 0x00FFFFFF)
//		//    break;
//		if (get_pixel(map, cur.x, cur.y)  != 0x000000FF)
//			draw_pixel(map, cur.x, cur.y, 0x000000FF);
//		error += deltaerr;
//		if (error >= 0.0)
//		{
//			cur.y += dir.y;
//			error -= 1.0;
//		}
//		/*if (get_pixel(map, cur.x, cur.y) == 0x00FFFFFF) {
//
//			printf("by\n");
//			return (((double) cur.y - (double) start.y) / delta.y);
//		}*/
//		cur.x += dir.x;
//		if (get_pixel(map, cur.x, cur.y) == 0x00FFFFFF) {
//
//			printf("ay\n");
//			return (((double) cur.x - (double) start.x) / delta.x);
//		}
//	}
//	printf("impact: (%d,%d)\n", cur.x, cur.y);
//	//return (((double)cur.x - (double)start.x)/delta.x);
//}

typedef struct  s_ray
{
	t_vec2d		position;
	double		direction;
	t_vec2d 	cur;
	int         xdir;
	int         ydir;
	double		x_step;
	double		y_step;
}               t_ray;

char hit_wall(t_frame *map, t_ray *ray, char dir)
{
	t_vec2i check_pos;

	//dir = '0';
	check_pos.x = (int)floor(ray->cur.x);
	check_pos.y = (int)floor(ray->cur.y);

	if (dir == 'h' && ray->ydir == -1)
		check_pos.y--;
	if (dir == 'v' && ray->xdir == -1)
		check_pos.x--;
							//	if (dir == 'v')
							//	{
							//		if (ray->xdir == -1)
							//			check_pos.x = (int)ceil((ray->cur.x));
							//		else if (ray->xdir == 1)
							//			check_pos.x = (int)floor((ray->cur.x));
							//	}
							//	else if (dir == 'h')
							//	{
							//		if (ray->ydir == -1)
							//			check_pos.y = (int)ceil((ray->cur.y));
							//		else if (ray->ydir == 1)
							//			check_pos.y = (int)floor((ray->cur.y));
							//	}
							//	printf("check_hit(%d,%d) -> %f rad *|", check_pos.x, check_pos.y, ray->direction);
	if(get_pixel(map, check_pos.x, check_pos.y) == 0x00FFFFFF || check_pos.x > 1000 || check_pos.y > 1000 || check_pos.x < 0 || check_pos.y < 0)
	{
		//printf("hit\n");
		return (1);
	}
	else
	{
		//printf("miss\n");
		return (0);
	}
}

double nearest_vertical_hit(t_frame *map, t_ray *ray/*, t_rc_renderer *renderer*/)
{
	double block_size = 1.0;
	//void *window;
	//t_vec2d cur;

	double dl, dr;

	//window = *((void **)ft_lmapget(renderer->windows, "minimap")->content);

	//printf("first wall: (%f,%f)\n", ray->cur.x, ray->cur.y);
	//printf("fmod Y: %f\n", fmod(ray->cur.y, block_size));
	//printf("fmod X: %f\n", fmod(ray->cur.x, block_size));

	dl = fmod(ray->cur.x, block_size);
	dr = block_size - fmod(ray->cur.x, block_size);

	//find first wall
	if (ray->xdir == 1)
	{
		ray->cur.y += dr * fabs(tan(ray->direction))  * ray->ydir;
		ray->cur.x += dr * ray->xdir;
	}
	else
	{
		ray->cur.y += dl * fabs(tan(ray->direction))  * ray->ydir;
		ray->cur.x += dl * ray->xdir;
	}

	//printf("first wall-v: (%f,%f)(%f,%f) - fmod: %f\n", ray->cur.x, ray->cur.y, ray->cur.x/16.0, ray->cur.y/16.0, fmod(ray->cur.y, block_size));
	//calculate x step and y step
	ray->y_step = block_size * fabs(tan(ray->direction)) * ray->ydir;
	ray->x_step = block_size * ray->xdir;
	while (!hit_wall(map, ray, 'v'))
	{
		//mlx_pixel_put(renderer->mlx, window, (int)ray->cur.x/16, (int)ray->cur.y/16, 0x003369E8);
		ray->cur.y += ray->y_step;
		ray->cur.x += ray->x_step;
	}
	//printf("impact-v: (%f,%f)\n", ray->cur.x, ray->cur.y);
	return ( sqrt(pow(ray->cur.x - ray->position.x, 2) + pow(ray->cur.y - ray->position.y, 2)));
}

double nearest_horizontal_hit(t_frame *map, t_ray *ray/*, t_rc_renderer *renderer*/)
{
	double block_size = 1.0;
	//void *window;

	double dt, db;
	dt = fmod(ray->cur.y, block_size);
	db = block_size - fmod(ray->cur.y, block_size);

	//window = *((void **)ft_lmapget(renderer->windows, "minimap")->content);
	if (ray->direction == 0.0)
		return (2147483647);

	//printf("fmod Y: %f\n", fmod(ray->cur.y, block_size));
	//printf("fmod X: %f\n", fmod(ray->cur.x, block_size));
	//find first wall
	if (ray->ydir == -1)
	{
		ray->cur.y += dt * ray->ydir;
		ray->cur.x += (dt / fabs(tan(ray->direction))) * ray->xdir;
	}
	else
	{
		ray->cur.y += db * ray->ydir;
		ray->cur.x += (db / fabs(tan(ray->direction))) * ray->xdir;
	}
	//printf("first wall-h: (%f,%f)(%f,%f) - fmod: %f\n", ray->cur.x, ray->cur.y, ray->cur.x/16.0, ray->cur.y/16.0, fmod(ray->cur.x, block_size));
	//calculate x step and y step
	ray->y_step = block_size * ray->ydir;
	ray->x_step = (block_size / fabs(tan(ray->direction))) * ray->xdir;
	while (!hit_wall(map, ray, 'h'))
	{
		//mlx_pixel_put(renderer->mlx, window, (int)ray->cur.x/16, (int)ray->cur.y/16, 0x003369E8);
		ray->cur.y += ray->y_step;
		ray->cur.x += ray->x_step;
	}
	//printf("impact-h: (%f,%f)\n", ray->cur.x, ray->cur.y);
	return ( sqrt(pow(ray->cur.x - ray->position.x, 2) + pow(ray->cur.y - ray->position.y, 2)));
}

double cast_ray(t_frame *map, t_vec2d position, double direction/*, t_rc_renderer *renderer*/, int *color)
{
	t_ray ray;
	double h_hit;
	double v_hit;

	ray.direction = direction;
	ray.position.x = (position.x)/* + 8.0f*/;
	ray.position.y = (position.y)/* + 8.0f*/ ;
	ray.ydir = (sin(direction) > 0) ? -1 : 1;
	ray.xdir = (cos(direction) > 0) ? 1 : -1;
	if (sin(direction) == 0)
		ray.ydir = 0;
	if (cos(direction) == 0)
		ray.xdir = 0;
	ray.cur = ray.position;

	//exit (1);

	h_hit = nearest_horizontal_hit(map, &ray/*, renderer*/);

	ray.cur = ray.position;
	v_hit = nearest_vertical_hit(map, &ray/*, renderer*/);

	if (h_hit < v_hit && ray.ydir == 1)
		*color = 0x00009925;
	else if (h_hit < v_hit)
		*color = 0x00D50F25;

	if (h_hit > v_hit && ray.xdir == 1)
		*color = 0x00EEB211;
	else if (h_hit > v_hit)
		*color = 0x003369E8;


	//printf("pos(%f,%f)(%f,%f) - fmod: (%f,%f)\n", ray.position.x, ray.position.y, ray.position.x/16.0, ray.position.y/16.0, fmod(ray.position.x, 16.0f), fmod(ray.position.y, 16.0f));
	//printf("fmod(opp side): (%f,%f)\n", 16.0f - fmod(ray.position.x, 16.0f), 16.0f - fmod(ray.position.y, 16.0f));
	//printf("length_h: %f \tlenght_v: %f\n", h_hit / 16.0f, v_hit / 16.0f);
	return ((h_hit < v_hit) ? h_hit/* / 16.0f*/ : v_hit/* / 16.0f*/);





	////////////////////////////////////////////////////////////////////////////
//	t_vec2i start;
//	t_vec2d delta;
//	double distance;
//
//	start.x = position.x;
//	start.y = position.y;
//	delta.x = cos(direction);
//	delta.y = sin(direction);
//	distance = 0.0;
//
//	if ((fabs(delta.y / delta.x) > 1.0f || delta.x == 0))
//		distance = castray_xmajor(map, start, delta);
//	else if (fabs(delta.y / delta.x) <= 1.0)
//		distance = castray_ymajor(map, start, delta);
//
//	return (distance);
	////////////////////////////////////////////////////////////////////////////
}


void draw_column(t_rc_renderer *renderer, int col_num, int length, int color)
{
	int i;

	int y_offset;

	y_offset = (renderer->win_y - length) / 2;

	i=0;
	while (i < length)
	{
		draw_pixel(renderer->scene->cur_frame, col_num, i + y_offset, color);
		i++;
	}
}
void graph(t_rc_renderer *renderer, int col_num, double length)
{
	int i;

	int y_offset;

	length *= 10;

	y_offset = (renderer->win_y - length);

	i=0;
	while (i < length)
	{
		draw_pixel(renderer->scene->cur_frame, col_num, i + y_offset, 0x00FFFFFF);
		i++;
	}
}

void	render_player_view(t_rc_renderer *renderer)
{
	t_player *player;
	double slice_height;
	double distance;
	int i;
	void *window;
	double cur_dir;
	int color;

	window = *((void **)ft_lmapget(renderer->windows, "Player View")->content);
	mlx_clear_window(renderer->mlx, window);
	//printf("%p\n", window);
	//ft_putstr("a\n");
	//ft_putstr("b\n");
	int z;
	int e;
	z = 0;
	while (z < renderer->scene->cur_frame->height)
	{
		e = 0;
		while(e < renderer->scene->cur_frame->width)
		{
			if (z <= renderer->scene->cur_frame->height / 2)
				draw_pixel(renderer->scene->cur_frame, e, z, 0x004286f4);
			else
				draw_pixel(renderer->scene->cur_frame, e, z, 0x0000aa30);
			e++;
		}
		z++;
	}

	i = 0;
	player = renderer->scene->player;
	cur_dir = player->direction + (player->fov / 2.0f);
	//
	//	<< loop start
	//printf("=============================================================================\n");
	while (i < renderer->win_x) {
		cur_dir -= player->fov / (double)renderer->win_x;
		//		cast rays (player, map)
		distance = cast_ray(renderer->scene->map, player->position, /*player->direction*/cur_dir/*, renderer*/, &color);
		//draw_player_ray(renderer, "minimap");
		//printf("ray: %d \tangle: %f\tlenght: %f pos(%f,%f)\n", i, cur_dir, distance, player->position.x, player->position.y);
		//		calculate slice height
		//if (cos(player->direction - cur_dir) == 0.0)
		//	slice_height = ((double)renderer->win_y / (distance));
		//else
			slice_height = ((double)renderer->win_y / (distance * cos(player->direction - cur_dir)));
		//ft_putnbr(slice_height);
		//ft_putchar('\n');
		//		draw slice to frame
		draw_column(renderer, i, (int)slice_height, color);
		//graph(renderer, i, distance);

		//	<< loop end
		i++;
	}
	//printf("=============================================================================\n");
	//ft_putstr("c\n");
	// display frame

	mlx_put_image_to_window(renderer->mlx, window, renderer->scene->cur_frame->id, 0, 0);
	mlx_string_put(renderer->mlx, window, 0, 0, 0x33FFFFFF, "FOV:");
	mlx_string_put(renderer->mlx, window, 40, 0, 0x33FFFFFF, ft_itoa(player->fov * (180.0f / 3.14f)));

	//ft_putstr("d\n");
	// destroy frame
	clear_frame(renderer->scene->cur_frame);

	//ft_putstr("e\n");
}

void	render_minimap( t_rc_renderer *renderer)
{
    void *window;

    window = *((void **)ft_lmapget(renderer->windows, "minimap")->content);

    //exit (1);
    //mlx_clear_window(renderer->mlx, window);

    //display map image for testing purposes
    mlx_put_image_to_window(renderer->mlx, window, renderer->scene->minimap->id, 0, 0);

    draw_player_ray(renderer, "minimap");

    mlx_pixel_put(renderer->mlx, window, renderer->scene->player->position.x,
                  renderer->scene->player->position.y,
                  0x00FF0000);
}

int			render_loop(void *param)
{
	t_rc_renderer	*renderer;

	renderer = (t_rc_renderer *)param;
	if (renderer->scene)
	{

		render_minimap(renderer);
		render_player_view(renderer);
	}
	return (0);
}

int		key_pressed(int keycode, void *param)
{
	t_rc_renderer	*renderer;

	renderer = (t_rc_renderer *)param;
	if (keycode == UP)
	{
		renderer->scene->player->position.y -= sin(renderer->scene->player->direction) / 4.0f;
		renderer->scene->player->position.x += cos(renderer->scene->player->direction) / 4.0f;
	}
	else if (keycode == DOWN)
	{
		renderer->scene->player->position.y += sin(renderer->scene->player->direction) / 4.0f;
		renderer->scene->player->position.x -= cos(renderer->scene->player->direction) / 4.0f;
	}
	else if (keycode == LEFT)
	{
		renderer->scene->player->position.y -= sin(renderer->scene->player->direction + 1.57f) / 4.0f;
		renderer->scene->player->position.x += cos(renderer->scene->player->direction + 1.57f) / 4.0f;
	}
	else if (keycode == RIGHT)
	{
		renderer->scene->player->position.y += sin(renderer->scene->player->direction + 1.57f) / 4.0f;
		renderer->scene->player->position.x -= cos(renderer->scene->player->direction + 1.57f) / 4.0f;
	}
	else if (keycode == A)
		renderer->scene->player->direction += 3.14f/32.0f;
	else if (keycode == D)
		renderer->scene->player->direction -= 3.14f/32.0f;
	else if (keycode == W)
		renderer->scene->player->fov += 3.14f/16.0f;
	else if (keycode == S)
		renderer->scene->player->fov -= 3.14f/16.0f;
	if (keycode == ESC)
		exit(1);
	render_loop(param);
	return (0);
}
int		exit_hook(t_rc_renderer *renderer)
{
	//cleanup
	if (renderer)
		free(renderer);
	exit(1);
}
int main(int argc, char **argv)
{
	int			    **array2d;
	t_rc_renderer	*rc_renderer;
	t_vec2i         *row_col;
	int				block_size;

	block_size = 1;
	if (argc != 2)
	{
		//usage
		return (0);
	}
	array2d = NULL;
	row_col = new_vec2i(0,0);
	//initalize ray caster
	rc_renderer = new_rc_renderer();
	//load map to a 2d array
	array2d = load_map(argv[1], row_col);
	//add window
	add_rcwindow(rc_renderer, row_col->x * block_size * 6, row_col->y * block_size * 6, ft_strdup("minimap"));
	add_rcwindow(rc_renderer, 1000, 1000, ft_strdup("Player View"));
	//construct an image map that will be used for casting rays
	rc_renderer->scene->map = construct_map(rc_renderer, array2d, block_size, row_col);
	rc_renderer->scene->cur_frame = new_tframe(rc_renderer, rc_renderer->win_x, rc_renderer->win_y);
	//ft_putstr("test\n");
	//free the memory used for the 2d array
	del_intArr(array2d, row_col->y);
	//ft_putstr("test\n");
	//add a player
	rc_renderer->scene->player = new_player(9, 29, 2.3561944902f, 1.02548);
	mlx_hook(*((void **)ft_lmapget(rc_renderer->windows, "minimap")->content), 2, 0, key_pressed, rc_renderer);
	mlx_hook(*((void **)ft_lmapget(rc_renderer->windows, "Player View")->content), 2, 0, key_pressed, rc_renderer);
	//mlx_loop_hook(rc_renderer->mlx, render_loop, rc_renderer);
	mlx_hook(*((void **)ft_lmapget(rc_renderer->windows, "minimap")->content), 17, 0, exit_hook, rc_renderer);
	mlx_hook(*((void **)ft_lmapget(rc_renderer->windows, "Player View")->content), 17, 0, exit_hook, rc_renderer);
	// run the mlx loop
	mlx_loop(rc_renderer->mlx);
	//clean up
	return (0);
}