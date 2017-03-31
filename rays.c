#include "wolf3d.h"

char	hit_wall(t_frame *map, t_ray *ray, char dir)
{
	t_vec2i	check_pos;
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

double	nearest_vertical_hit(t_frame *map, t_ray *ray)
{
	double	block_size;
	double	dl;
	double	dr;

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

double	nearest_horizontal_hit(t_frame *map, t_ray *ray)
{
	double	block_size;
	double	dt;
	double	db;

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

t_ray	construct_ray(t_vec2d position, double direction)
{
	t_ray	ray;

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

double	cast_ray(t_frame *map, t_vec2d position, double direction, int *color)
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
