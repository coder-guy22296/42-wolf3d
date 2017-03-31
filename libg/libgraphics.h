/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgraphics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:59:14 by cyildiri          #+#    #+#             */
/*   Updated: 2016/11/21 22:45:51 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGRAPHICS_H
# define LIBGRAPHICS_H

# include <math.h>
# include "libft.h"
# include "mlx.h"

# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define PAGE_UP 116
# define PAGE_DOWN 121

# define NUM_7 89
# define NUM_9 92
# define NUM_8 91
# define NUM_5 87
# define NUM_4 86
# define NUM_6 88
# define NUM_1 83

# define W 13
# define S 1
# define A 0
# define D 2
# define R 15
# define F 3

# define NUM_0 82
# define NUM_3 85
# define NUM_DOT 65
# define ESC 53

# define ALPHA 24
# define RED 16
# define GREEN 8
# define BLUE 0

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
	int			alpha;
}				t_color;

typedef struct	s_vec2i
{
	int			x;
	int			y;
}				t_vec2i;

typedef struct	s_vec2fc
{
	float		x;
	float		y;
	int			color;
}				t_vec2fc;

typedef struct	s_vec3fc
{
	float		x;
	float		y;
	float		z;
	int			color;
}				t_vec3fc;

typedef struct	s_vec6f
{
	t_vec3fc	position;
	t_vec3fc	rotation;
}				t_vec6f;

typedef struct	s_3d_object
{
	int			*faces_arr;
	int			face_cnt;
	int			*vertex_ind;
	float		z_max;
	float		z_min;
	t_vec3fc	*vertices;
	int			vertex_cnt;
	t_vec6f		pos_vector;
	void		(*transform)(struct	s_3d_object obj);
}				t_3d_object;

typedef struct	s_camera
{
	t_vec6f		loc;
	t_vec3fc	viewer;
}				t_camera;

typedef struct	s_frame
{
	void	*id;
	char	*image;
	int		height;
	int		width;
	int		color_depth;
	int		endien;
	int		line_size;
}				t_frame;

typedef struct	s_scene
{
	t_vec3fc	origin_point;
	t_camera	*camera;
	t_list		*objects;
	int			active_obj;
	t_frame		cur_frame;
	t_vec3fc	scale;
	t_vec3fc	(*projection_method)(struct s_scene scene, t_vec3fc point);
}				t_scene;

typedef struct	s_renderer
{
	void		*mlx;
	void		*window;
	int			win_x;
	int			win_y;
	t_scene		*scene;
	t_vec2fc	last_click;

	void		(*render)(struct s_renderer *renderer, t_scene scene);
}				t_renderer;

typedef struct	s_line
{
	t_vec3fc	start;
	t_vec2i		cur;
	t_vec3fc	end;
	t_vec2i		delta;
	t_vec2i		dir;
	double		slope;
}				t_line;

t_color			color(int color32);
int				blend(int color_a, int color_b, float percentage);
t_vec2i			*new_vec2i(int x, int y);
t_vec2fc		*new_vec2f(float x, float y);
t_vec3fc		*new_vec3f(float x, float y, float z);
t_vec6f			*new_vec6f(t_vec3fc pos, t_vec3fc rot);
t_3d_object		*new_3d_object(char *filename);
t_frame			new_frame(int height, int width);
void			add_window(t_renderer *renderer, int width, int height,
							char *title);
int				frame_pixel_put(t_scene *scene, t_vec2fc place_me);
int				blend(int color_a, int color_b, float percentage);
t_camera		*new_camera(t_vec6f camera_loc, t_vec3fc viewer_loc);
t_scene			*new_scene(t_vec3fc (*projection)(t_scene scene,
							t_vec3fc point), int frame_height, int frame_width);
t_renderer		*new_renderer(void (*render)(t_renderer *, t_scene));
void			del_3d_object(t_3d_object *obj);
void			del_scene(t_scene *scene);
void			del_renderer(t_renderer *renderer);
t_vec3fc		perspective_projection(t_scene scene, t_vec3fc point);
t_vec3fc		orthographic_projection(t_scene scene, t_vec3fc point);
t_vec3fc		translate_point(t_vec3fc original, t_vec3fc translation);
void			rotate_object(t_3d_object *obj, t_vec3fc rotation);
void			drawline(t_renderer *renderer, t_vec3fc point_a,
							t_vec3fc point_b);
void			drawline3d(t_renderer *renderer, t_vec3fc point_a,
							t_vec3fc point_b);
void			render3d_object(t_renderer *renderer, t_3d_object obj);
void			render_scene(t_renderer *renderer, t_scene scene);
void			add_object(t_scene *scene, t_3d_object *obj);
void			rem_object(t_scene *scene, t_3d_object *obj);
t_vec2i			vec2i(int x, int y);
t_vec2fc		vec2fc(float x, float y, int color);
t_vec2fc		vec2f(float x, float y);
t_vec3fc		vec3f(float x, float y, float z);
t_vec3fc		vec3fc(float x, float y, float z, int color);
t_vec6f			vec6f(t_vec3fc pos, t_vec3fc rot);
t_camera		camera(t_vec6f camera_loc, t_vec3fc viewer_loc);
t_scene			scene(t_vec3fc (*projection)(t_scene scene, t_vec3fc point),
							int frame_height, int frame_width);
t_renderer		renderer(void (*render)(t_renderer *, t_scene));

#endif
