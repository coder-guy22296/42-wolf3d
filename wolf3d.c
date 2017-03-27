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

typedef struct  s_minimap
{
	t_player    *player;
	t_frame     *map;
	t_frame     *overlay;
	double      alpha;
	t_vec2i     position;
	double      scaling;
}               t_minimap;

typedef struct	s_rc_scene
{
	t_frame		*map;
	t_minimap	*minimap;
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

t_frame *frame_resize(t_rc_renderer *renderer, t_frame *original, double scaling)
{
	t_vec2i cur;
	t_frame *scaled_frame;

	scaled_frame = new_tframe(renderer, original->height * scaling,
							  original->width * scaling);
	cur.y = 0;
	while (cur.y < original->height)
	{
		cur.x = 0;
		while (cur.x < original->width)
		{
			if (get_pixel(original, cur.x, cur.y) != 0)
			{
				draw_square(scaled_frame, cur.x * scaling, cur.y * scaling, scaling * 1);
			}
			cur.x++;
		}
		cur.y++;
	}
	return (scaled_frame);
}

void frame_clear(t_frame *frame)
{
	int i;
	int j;

	i = 0;
	while (i < frame->height)
	{
		j = 0;
		while (j < frame->width)
		{
			draw_pixel(frame, j, i, 0xFF000000);
			j++;
		}
		i++;
	}
}

int apply_alpha(int original_color, double alpha)
{
	int solid_color;
	int alpha_color;

	solid_color = original_color & 0x00FFFFFF;
	alpha_color = solid_color | ((int)((1.00f - alpha) * 255)) << 24;
	return (alpha_color);
}

void frame_apply_alpha(t_frame *frame, double alpha)
{
	int i;
	int j;
	int color;

	i = 0;
	while (i < frame->height)
	{
		j = 0;
		while (j < frame->width)
		{
			color = get_pixel(frame, j, i);
			draw_pixel(frame, j, i, apply_alpha(color, alpha));
			j++;
		}
		i++;
	}
}

void frame_delete(t_rc_renderer *rc_renderer, t_frame **delete_me)
{

	mlx_destroy_image(rc_renderer->mlx, (*delete_me)->image);
	free((*delete_me)->id);
	free(*delete_me);
	*delete_me = NULL;
}

t_minimap *new_minimap(t_rc_renderer *renderer, t_frame *rc_map, t_vec2i pos, double scaling)
{
	t_minimap *minimap;

	if (!(minimap = (t_minimap *)ft_memalloc(sizeof(t_minimap))))
		return (NULL);
	minimap->map = frame_resize(renderer, rc_map, scaling);
	minimap->overlay = new_tframe(renderer, minimap->map->height, minimap->map->width);
	minimap->scaling = scaling;
	minimap->alpha = 1.0f;
	frame_apply_alpha(minimap->map, 1.0f);
	minimap->position = pos;
	return (minimap);
}

void minimap_add_player(t_minimap *minimap, t_player *player)
{
	minimap->player = player;
}

void minimap_set_pos(t_minimap *minimap, t_vec2i pos)
{
	minimap->position = pos;
}

void minimap_set_alpha(t_minimap *minimap, double transparency)
{
	frame_apply_alpha(minimap->map, transparency);
	minimap->alpha = transparency;
}

void minimap_change_map(t_rc_renderer *renderer, t_minimap *minimap, t_frame *rc_map, double scaling)
{
	frame_delete(renderer, &minimap->map);
	frame_delete(renderer, &minimap->overlay);
	minimap->map = frame_resize(renderer, rc_map, scaling);
	minimap->overlay = new_tframe(renderer, minimap->map->height, minimap->map->width);
}

static void		drawray_xmajor(t_minimap *minimap, t_vec2i start, t_vec2d delta, int color)
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
	while (1)
	{
		if ((get_pixel(minimap->map, cur.x, cur.y) & 0x00FFFFFF) != 0)
			break;
		if (cur.y == start.y)
			error += deltaerr;
		draw_pixel(minimap->overlay, cur.x, cur.y, color);
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

static void		drawray_ymajor(t_minimap *minimap, t_vec2i start, t_vec2d delta, int color)
{
	double	deltaerr;
	double	error;
	t_vec2i cur;
	t_vec2i dir;

	cur = start;
	dir.x = (delta.x < 0) ? -1 : 1;
	dir.y = (delta.y < 0) ? -1 : 1;
	error = -1.0;
	deltaerr = fabs(delta.y / delta.x);
	error += deltaerr;
	while (1)
	{
		if ((get_pixel(minimap->map, cur.x, cur.y) & 0x00FFFFFF) != 0)
			break;
		draw_pixel(minimap->overlay, cur.x, cur.y, color);
		error += deltaerr;
		if (error >= 0.0)
		{
			cur.y += dir.y;
			error -= 1.0;
		}
		cur.x += dir.x;
	}
}

void minimap_draw_ray(t_minimap *minimap, t_vec2d pos, double direction, int color)
{
	t_vec2i start;
	t_vec2d delta;

	start.x = pos.x;
	start.y = pos.y;
	delta.x = cos(direction);
	delta.y = sin(direction) * -1.0f;

	if ((fabs(delta.y / delta.x) > 1.0f || delta.x == 0))
		drawray_xmajor(minimap, start, delta, color);
	else if (fabs(delta.y / delta.x) <= 1.0)
		drawray_ymajor(minimap, start, delta, color);


}

void minimap_render(t_rc_renderer *renderer, t_minimap *minimap, char *window_name)
{
	void *window;
	t_vec2d pos;

	window = *((void **)ft_lmapget(renderer->windows, window_name)->content);
	mlx_put_image_to_window(renderer->mlx, window, minimap->map->id, minimap->position.x, minimap->position.y);
	frame_clear(minimap->overlay);
	pos = minimap->player->position;
	pos.x *= minimap->scaling;
	pos.y *= minimap->scaling;
	minimap_draw_ray(minimap, pos, minimap->player->direction, 0x000000FF);
	draw_pixel(minimap->overlay, pos.x,
			   pos.y,
				  0x00FF0000);
	mlx_put_image_to_window(renderer->mlx, window, minimap->overlay->id, minimap->position.x, minimap->position.y);
}

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
	ft_lmapadd(&renderer->windows, to_add);
    if (!(renderer->win_x))
    {
        renderer->win_x = width;
        renderer->win_y = height;
    }
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

// hmm, where is the map then? *tsk* *tsk* *tsk*
t_frame *construct_map(t_rc_renderer *renderer, int **array2d, int block_size, t_vec2i *row_col)
{
	t_frame *frame;
	int i;
	int j;

	//malloc frame
	frame = new_tframe(renderer, row_col->y * block_size, row_col->x * block_size);
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

	check_pos.x = (int)floor(ray->cur.x);
	check_pos.y = (int)floor(ray->cur.y);

	if (dir == 'h' && ray->ydir == -1)
		check_pos.y--;
	if (dir == 'v' && ray->xdir == -1)
		check_pos.x--;
	if(get_pixel(map, check_pos.x, check_pos.y) == 0x00FFFFFF || check_pos.x > 1000 || check_pos.y > 1000 || check_pos.x < 0 || check_pos.y < 0)
		return (1);
	else
		return (0);
}

double nearest_vertical_hit(t_frame *map, t_ray *ray)
{
	double block_size = 1.0;
	double dl, dr;

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

	//calculate x step and y step
	ray->y_step = block_size * fabs(tan(ray->direction)) * ray->ydir;
	ray->x_step = block_size * ray->xdir;
	while (!hit_wall(map, ray, 'v'))
	{
		ray->cur.y += ray->y_step;
		ray->cur.x += ray->x_step;
	}
	return ( sqrt(pow(ray->cur.x - ray->position.x, 2) + pow(ray->cur.y - ray->position.y, 2)));
}

double nearest_horizontal_hit(t_frame *map, t_ray *ray)
{
	double block_size = 1.0;
	double dt, db;

	dt = fmod(ray->cur.y, block_size);
	db = block_size - fmod(ray->cur.y, block_size);
	if (ray->direction == 0.0)
        return (2147483647);

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
	//calculate x step and y step
	ray->y_step = block_size * ray->ydir;
	ray->x_step = (block_size / fabs(tan(ray->direction))) * ray->xdir;
	while (!hit_wall(map, ray, 'h'))
	{
		ray->cur.y += ray->y_step;
		ray->cur.x += ray->x_step;
	}
	return ( sqrt(pow(ray->cur.x - ray->position.x, 2) + pow(ray->cur.y - ray->position.y, 2)));
}

double cast_ray(t_frame *map, t_vec2d position, double direction, int *color)
{
	t_ray ray;
	double h_hit;
	double v_hit;

	ray.direction = direction;
	ray.position.x = (position.x);
	ray.position.y = (position.y);
	ray.ydir = (sin(direction) > 0) ? -1 : 1;
	ray.xdir = (cos(direction) > 0) ? 1 : -1;
	if (sin(direction) == 0)
		ray.ydir = 0;
	if (cos(direction) == 0)
		ray.xdir = 0;
	ray.cur = ray.position;
	h_hit = nearest_horizontal_hit(map, &ray);

	ray.cur = ray.position;
	v_hit = nearest_vertical_hit(map, &ray);
	if (h_hit < v_hit && ray.ydir == 1)
		*color = 0x00009925;
	else if (h_hit < v_hit)
		*color = 0x00D50F25;
	if (h_hit > v_hit && ray.xdir == 1)
		*color = 0x00EEB211;
	else if (h_hit > v_hit)
		*color = 0x003369E8;
	return ((h_hit < v_hit) ? h_hit : v_hit);
}

void draw_column(t_rc_renderer *renderer, int col_num, int length, int color)
{
	int i;

	int y_offset;

	y_offset = (renderer->win_y - length) / 2;
	i = 0;
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

	i = 0;
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
    int z;
    int e;

	window = *((void **)ft_lmapget(renderer->windows, "Player View")->content);
	mlx_clear_window(renderer->mlx, window);
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
		distance = cast_ray(renderer->scene->map, player->position, cur_dir, &color);
        //		calculate slice height
        slice_height = ((double)renderer->win_y / (distance * cos(player->direction - cur_dir)));
		//		draw slice to frame
		draw_column(renderer, i, (int)slice_height, color);
		i++;
	}
    //printf("=============================================================================\n");
    //	<< loop end

	// display frame
	mlx_put_image_to_window(renderer->mlx, window, renderer->scene->cur_frame->id, 0, 0);
	mlx_string_put(renderer->mlx, window, 0, 0, 0x33FFFFFF, "FOV:");
	mlx_string_put(renderer->mlx, window, 40, 0, 0x33FFFFFF, ft_itoa(player->fov * (180.0f / 3.14f)));
	minimap_render(renderer, renderer->scene->minimap, "Player View");

	// destroy frame
	frame_clear(renderer->scene->cur_frame);
}

void	render_minimap_window( t_rc_renderer *renderer)
{
	void *window;

	window = *((void **)ft_lmapget(renderer->windows, "minimap")->content);
	if (!window)
		exit (1);
	mlx_clear_window(renderer->mlx, window);

	//display map image for testing purposes
	mlx_put_image_to_window(renderer->mlx, window, renderer->scene->minimap->map->id, 0, 0);
}

int			render_loop(void *param)
{
	t_rc_renderer	*renderer;

	renderer = (t_rc_renderer *)param;
	if (renderer->scene)
	{
        render_minimap_window(renderer);
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

	add_rcwindow(rc_renderer, 1000, 1000, ft_strdup("Player View"));
	//construct an image map that will be used for casting rays
	rc_renderer->scene->map = construct_map(rc_renderer, array2d, block_size, row_col);
	rc_renderer->scene->cur_frame = new_tframe(rc_renderer, rc_renderer->win_x, rc_renderer->win_y);
	rc_renderer->scene->minimap = new_minimap(rc_renderer, rc_renderer->scene->map, vec2i(800, 800), 6.0);
	//free the memory used for the 2d array
	del_intArr(array2d, row_col->y);
	//add a player
	rc_renderer->scene->player = new_player(9, 29, 2.3561944902f, 1.02548);
	minimap_add_player(rc_renderer->scene->minimap, rc_renderer->scene->player);
	minimap_set_alpha(rc_renderer->scene->minimap, 0.8);
    add_rcwindow(rc_renderer, rc_renderer->scene->minimap->map->height, rc_renderer->scene->minimap->map->width, ft_strdup("minimap"));
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