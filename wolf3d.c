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
	int			height;
	int			width;
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

t_frame		*new_tframe(t_rc_renderer *rend, int height, int width)
{
	t_frame *frame;

	if(!(frame = (t_frame *)ft_memalloc(sizeof(t_frame))))
		return (0);
	frame->id = mlx_new_image(rend->mlx, width, height);
	frame->image = mlx_get_data_addr(
            frame->id,
            &frame->color_depth,
            &frame->line_size,
            &frame->endien);
	frame->height = height;
	frame->width = width;
	return (frame);
}

int 	frame_draw_pixel(t_frame *frame, int x, int y, int color)
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

int frame_get_pixel(t_frame *frame, int x, int y)
{
	unsigned int	*image;
	int				pos;

	image = (unsigned int *)frame->image;
	if (x < 0 || x >= frame->width || y < 0 || y >= frame->height)
	{
		return (1);
	}
	pos = x + (y * frame->line_size / 4);
	return (image[pos]);
}

void frame_draw_square(t_frame *frame, int x, int y, int size)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			frame_draw_pixel(frame, x + j, y + i, 0x00FFFFFF);
			j++;
		}
		i++;
	}
}

t_frame *frame_resize(t_rc_renderer *rend, t_frame *orig, double scaling)
{
	t_vec2i cur;
	t_frame *scaled_frame;
    t_vec2i size;
    t_vec2i new_pos;

    size.y = orig->height * scaling;
    size.x = orig->width * scaling;
	scaled_frame = new_tframe(rend, size.y, size.x);
	cur.y = 0;
	while (cur.y < orig->height)
	{
		cur.x = 0;
		while (cur.x < orig->width)
		{
            new_pos.x = cur.x * scaling;
            new_pos.y = cur.y * scaling;
			if (frame_get_pixel(orig, cur.x, cur.y) != 0)
			{
				frame_draw_square(scaled_frame, new_pos.x, new_pos.y, scaling);
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
			frame_draw_pixel(frame, j, i, 0xFF000000);
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
			color = frame_get_pixel(frame, j, i);
			frame_draw_pixel(frame, j, i, apply_alpha(color, alpha));
			j++;
		}
		i++;
	}
}

void frame_delete(t_rc_renderer *rend, t_frame **delete_me)
{

	mlx_destroy_image(rend->mlx, (*delete_me)->image);
	free((*delete_me)->id);
	free(*delete_me);
	*delete_me = NULL;
}

t_minimap *new_minimap(t_rc_renderer *rend, t_frame *rc_map, t_vec2i pos,
double scaling)
{
	t_minimap *minimap;

	if (!(minimap = (t_minimap *)ft_memalloc(sizeof(t_minimap))))
		return (NULL);
	minimap->map = frame_resize(rend, rc_map, scaling);
	minimap->height = minimap->map->height;
	minimap->width = minimap->map->width;
	minimap->overlay = new_tframe(rend, minimap->height, minimap->width);
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

void minimap_change_map(t_rc_renderer *rend, t_minimap *mini, t_frame *rc_map,
double scaling)
{
	frame_delete(rend, &mini->map);
	frame_delete(rend, &mini->overlay);
	mini->map = frame_resize(rend, rc_map, scaling);
	mini->height = mini->map->height;
	mini->width = mini->map->width;
	mini->overlay = new_tframe(rend, mini->height, mini->width);
}

static void		drawray_xmajor(t_minimap *minimap, t_vec2i start, t_vec2d delta,
int color)
{
	double	deltaerr;
	double	error;
	t_vec2i cur;
	t_vec2i dir;

	cur = start;
	dir.x = (delta.x < 0) ? -1 : 1;
	dir.y = (delta.y < 0) ? -1 : 1;
	error = -1.0;
	deltaerr = fabs(delta.x / delta.y);
	error += deltaerr;
	while ((frame_get_pixel(minimap->map, cur.x, cur.y) & 0x00FFFFFF) == 0)
	{
		frame_draw_pixel(minimap->overlay, cur.x, cur.y, color);
		error += deltaerr;
		if (error >= 0.0)
		{
			cur.x += dir.x;
			error -= 1.0;
		}
		cur.y += dir.y;
	}
}

static void		drawray_ymajor(t_minimap *minimap, t_vec2i start, t_vec2d delta,
int color)
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
	while ((frame_get_pixel(minimap->map, cur.x, cur.y) & 0x00FFFFFF) == 0)
	{
		frame_draw_pixel(minimap->overlay, cur.x, cur.y, color);
		error += deltaerr;
		if (error >= 0.0)
		{
			cur.y += dir.y;
			error -= 1.0;
		}
		cur.x += dir.x;
	}
}

void minimap_draw_ray(t_minimap *minimap, t_vec2d pos, double direction,
int color)
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

/*
** draws player direction and position on the minimap overlay, then places the
** minimap and minimap overlay on the player window at its position specified
** in the minimap struct
*/

void minimap_render(t_rc_renderer *rend, t_minimap *minimap, char *window_name)
{
	void	*window;
	t_vec2i map_pos;
	t_vec2d player_pos;
	double	player_dir;

	window = *((void **)ft_lmapget(rend->windows, window_name)->content);
	map_pos.x = minimap->position.x;
	map_pos.y = minimap->position.y;
	player_pos = minimap->player->position;
	player_pos.x *= minimap->scaling;
	player_pos.y *= minimap->scaling;
	player_dir = minimap->player->direction;
	frame_clear(minimap->overlay);
	mlx_put_image_to_window(rend->mlx, window, minimap->map->id, map_pos.x,
	map_pos.y);
	minimap_draw_ray(minimap, player_pos, player_dir, 0x000000FF);
	frame_draw_pixel(minimap->overlay, player_pos.x, player_pos.y, 0x00FF0000);
	mlx_put_image_to_window(rend->mlx, window, minimap->overlay->id, map_pos.x,
	map_pos.y);
}

t_rc_renderer	*new_rc_renderer()
{
	t_rc_renderer	*rc_renderer;

	if (!(rc_renderer = (t_rc_renderer *)ft_memalloc(sizeof(t_rc_renderer))))
		return (NULL);
	if (!(rc_renderer->scene = (t_rc_scene *)ft_memalloc(sizeof(t_rc_scene))))
		return (NULL);
	rc_renderer->mlx = mlx_init();
	return (rc_renderer);
}

void	add_rcwindow(t_rc_renderer *rend, int width, int height, char *title)
{
	t_lmap	*to_add;
	void	*new_window;

	new_window = mlx_new_window(rend->mlx, width, height, title);
	to_add = ft_lmapnew(title, sizeof(title), &new_window, sizeof(new_window));
	ft_lmapadd(&rend->windows, to_add);
    if (!(rend->win_x))
    {
        rend->win_x = width;
        rend->win_y = height;
    }
}

void del_intArr(int **arr, int rows)
{
	int	i;

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

/*
** hmm, where is the map then? *tsk* *tsk* *tsk*
*/
t_frame *construct_map(t_rc_renderer *rend, int **array2d, int block_size,
t_vec2i *row_col)
{
	t_frame	*frame;
	int		i;
	int		j;

	frame = new_tframe(rend, row_col->y * block_size, row_col->x * block_size);
	i = 0;
	while (i < row_col->y)
	{
		j = 0;
		while (j < row_col->x)
		{
			if (array2d[i][j] == 1)
			{
				frame_draw_square(frame, j * block_size, i * block_size,
				block_size);
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
	int		pos_color;

	check_pos.x = (int)floor(ray->cur.x);
	check_pos.y = (int)floor(ray->cur.y);
	if (dir == 'h' && ray->ydir == -1)
		check_pos.y--;
	if (dir == 'v' && ray->xdir == -1)
		check_pos.x--;
	pos_color = frame_get_pixel(map, check_pos.x, check_pos.y);
	if ( pos_color == 0x00FFFFFF || pos_color == 1)
		return (1);
	else
		return (0);
}

double distance(t_vec2d point_a, t_vec2d point_b)
{
	double a_squared;
	double b_squared;

	a_squared = pow(point_a.x - point_b.x, 2);
	b_squared = pow(point_a.y - point_b.y, 2);
	return ( sqrt(a_squared + b_squared) );
}

double nearest_vertical_hit(t_frame *map, t_ray *ray)
{
	double block_size;
	double dl;
	double dr;

	block_size = 1.0;
    dl = fmod(ray->cur.x, block_size);
    dr = block_size - fmod(ray->cur.x, block_size);
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
	ray->y_step = block_size * fabs(tan(ray->direction)) * ray->ydir;
	ray->x_step = block_size * ray->xdir;
	while (!hit_wall(map, ray, 'v'))
	{
		ray->cur.y += ray->y_step;
		ray->cur.x += ray->x_step;
	}
	return ( distance(ray->cur, ray->position) );
}

double nearest_horizontal_hit(t_frame *map, t_ray *ray)
{
	double block_size;
	double dt;
	double db;

	block_size = 1.0;
	dt = fmod(ray->cur.y, block_size);
	db = block_size - fmod(ray->cur.y, block_size);
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
	ray->y_step = block_size * ray->ydir;
	ray->x_step = (block_size / fabs(tan(ray->direction))) * ray->xdir;
	while (!hit_wall(map, ray, 'h'))
	{
		ray->cur.y += ray->y_step;
		ray->cur.x += ray->x_step;
	}
	return ( distance(ray->cur, ray->position) );
}

t_ray construct_ray(t_vec2d position, double direction)
{
	t_ray ray;

	ft_bzero(&ray, sizeof(t_ray));
	ray.direction = direction;
	ray.position.x = (position.x);
	ray.position.y = (position.y);
	ray.ydir = (sin(direction) > 0) ? -1 : 1;
	ray.xdir = (cos(direction) > 0) ? 1 : -1;
	if (sin(direction) == 0)
		ray.ydir = 0;
	if (cos(direction) == 0)
		ray.xdir = 0;
	return (ray);
}

double cast_ray(t_frame *map, t_vec2d position, double direction, int *color)
{
	t_ray	ray;
	double	h_hit;
	double	v_hit;

	ray = construct_ray(position, direction);
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

void draw_column(t_frame *frame, int col_num, int length, int color)
{
	int i;
	int y_offset;

	y_offset = (frame->height - length) / 2;
	i = 0;
	while (i < length)
	{
		frame_draw_pixel(frame, col_num, i + y_offset, color);
		i++;
	}
}

void draw_floor_ceiling(t_frame *frame, int floor_color, int ceil_color)
{
	t_vec2i cur_pixel;

	cur_pixel.y = 0;
	while (cur_pixel.y < frame->height)
	{
		cur_pixel.x = 0;
		while(cur_pixel.x < frame->width)
		{
			if (cur_pixel.y <= frame->height / 2)
				frame_draw_pixel(frame, cur_pixel.x, cur_pixel.y, floor_color);
			else
				frame_draw_pixel(frame, cur_pixel.x, cur_pixel.y, ceil_color);
			cur_pixel.x++;
		}
		cur_pixel.y++;
	}
}

void draw_walls(t_frame *frame, t_frame *rc_map, t_player *player)
{
	double	cur_dir;
	int		cur_column;
	double	distance;
	double	column_height;
	int		color;

	cur_dir = player->direction + (player->fov / 2.0f);
	cur_column = 0;
	while (cur_column < frame->width)
	{
		cur_dir -= player->fov / (double)frame->width;
		distance = cast_ray(rc_map, player->position, cur_dir, &color);
		column_height = ((double)frame->height
						/ (distance * cos(player->direction - cur_dir)));
		draw_column(frame, cur_column, (int)column_height, color);
		cur_column++;
	}
}

void	render_player_view(t_rc_renderer *rend)
{
	void		*window;
	t_frame		*cur_frame;
	t_player	*player;

	window = *((void **)ft_lmapget(rend->windows, "Player View")->content);
	cur_frame = rend->scene->cur_frame;
	player = rend->scene->player;
	mlx_clear_window(rend->mlx, window);
	draw_floor_ceiling(cur_frame, 0x004286f4, 0x0000aa30);
	draw_walls(cur_frame, rend->scene->map, rend->scene->player);
	mlx_put_image_to_window(rend->mlx, window, cur_frame->id, 0, 0);
	mlx_string_put(rend->mlx, window, 0, 0, 0x33FFFFFF, "FOV:");
	mlx_string_put(rend->mlx, window, 40, 0,
	0x33FFFFFF, ft_itoa(player->fov * (180.0f / 3.14f)));
	minimap_render(rend, rend->scene->minimap, "Player View");
	frame_clear(cur_frame);
}

void	render_minimap_window( t_rc_renderer *rend)
{
	void	*window;
	t_frame	*rc_map;

	window = *((void **)ft_lmapget(rend->windows, "minimap")->content);
	rc_map = rend->scene->minimap->map;
	if (!window)
		exit (1);
	mlx_clear_window(rend->mlx, window);
	mlx_put_image_to_window(rend->mlx, window, rc_map->id, 0, 0);
}

int			render_loop(void *param)
{
	t_rc_renderer	*rend;

	rend = (t_rc_renderer *)param;
	if (rend->scene)
	{
        render_minimap_window(rend);
		render_player_view(rend);
	}
	return (0);
}

void	player_translation_controls(int keycode, t_player *player)
{
	if (keycode == UP)
	{
		player->position.y -= sin(player->direction) / 4.0f;
		player->position.x += cos(player->direction) / 4.0f;
	}
	else if (keycode == DOWN)
	{
		player->position.y += sin(player->direction) / 4.0f;
		player->position.x -= cos(player->direction) / 4.0f;
	}
	else if (keycode == LEFT)
	{
		player->position.y -= sin(player->direction + 1.57f) / 4.0f;
		player->position.x += cos(player->direction + 1.57f) / 4.0f;
	}
	else if (keycode == RIGHT)
	{
		player->position.y += sin(player->direction + 1.57f) / 4.0f;
		player->position.x -= cos(player->direction + 1.57f) / 4.0f;
	}
}

void player_rotation_controls(int keycode, t_player *player)
{
	if (keycode == A)
		player->direction += 3.14f/32.0f;
	else if (keycode == D)
		player->direction -= 3.14f/32.0f;
}

void player_fov_controls(int keycode, t_player *player)
{
	if (keycode == W)
		player->fov += 3.14f/16.0f;
	else if (keycode == S)
		player->fov -= 3.14f/16.0f;
}

int		exit_hook(t_rc_renderer *rend)
{
	if (rend)
		free(rend);
	exit(1);
}

int		key_pressed(int keycode, void *param)
{
	t_rc_renderer	*rend;
	t_player		*player;

	rend = (t_rc_renderer *)param;
	player = rend->scene->player;
	player_translation_controls(keycode, player);
	player_rotation_controls(keycode, player);
	player_fov_controls(keycode, player);
	if (keycode == ESC)
		exit_hook(rend);
	return (0);
}

void *get_window(t_rc_renderer *rend, char *window_name)
{
	t_lmap	*element;
	void	*window;
	
	element = ft_lmapget(rend->windows, window_name);
	window = *((void **)element->content);
	return (window);
}

void hooks(t_rc_renderer *rend)
{
	mlx_hook(get_window(rend, "minimap"), 2, 0, key_pressed, rend);
	mlx_hook(get_window(rend, "Player View"), 2, 0, key_pressed, rend);
	mlx_loop_hook(rend->mlx, render_loop, rend);
	mlx_hook(get_window(rend, "minimap"), 17, 0, exit_hook, rend);
	mlx_hook(get_window(rend, "Player View"), 17, 0, exit_hook, rend);
	mlx_loop(rend->mlx);
}

int main(int argc, char **argv)
{
	int			    **array2d;
	t_rc_renderer	*rend;
	t_vec2i         *row_col;
	int				block_size;

	block_size = 1;
	if (argc != 2)
	{
		ft_putstr("usage: ./wolf3d <wolf file>\n");
		return (0);
	}
	array2d = NULL;
	row_col = new_vec2i(0,0);
	rend = new_rc_renderer();
	array2d = load_map(argv[1], row_col);
	add_rcwindow(rend, 1000, 1000, ft_strdup("Player View"));
	rend->scene->map = construct_map(rend, array2d, block_size, row_col);
	rend->scene->cur_frame = new_tframe(rend, rend->win_x, rend->win_y);
	rend->scene->minimap = new_minimap(rend, rend->scene->map, vec2i(800, 800), 6.0);
	del_intArr(array2d, row_col->y);
	rend->scene->player = new_player(9, 29, 2.3561944902f, 1.02548);
	minimap_add_player(rend->scene->minimap, rend->scene->player);
	minimap_set_alpha(rend->scene->minimap, 0.8);
    add_rcwindow(rend, rend->scene->minimap->map->height, rend->scene->minimap->map->width, ft_strdup("minimap"));
	hooks(rend);
	return (0);
}