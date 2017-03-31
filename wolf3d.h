/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 22:59:13 by cyildiri          #+#    #+#             */
/*   Updated: 2017/03/30 18:09:11 by cyildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libgraphics.h"

typedef struct	s_vec2f
{
	float		x;
	float		y;
}				t_vec2f;

typedef struct	s_vec2d
{
	double		x;
	double		y;
}				t_vec2d;

typedef struct	s_player
{
	t_vec2d		position;
	double		direction;
	double		fov;

}				t_player;

typedef struct	s_minimap
{
	t_player	*player;
	t_frame		*map;
	t_frame		*overlay;
	double		alpha;
	t_vec2i		position;
	int			height;
	int			width;
	double		scaling;
}				t_minimap;

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
	t_lmap		*windows;
	int			win_x;
	int			win_y;
	t_rc_scene	*scene;
}				t_rc_renderer;

typedef struct	s_ray
{
	t_vec2d		position;
	double		direction;
	t_vec2d		cur;
	int			xdir;
	int			ydir;
	double		x_step;
	double		y_step;
}				t_ray;

void			*get_rcwindow(t_rc_renderer *rend, char *window_name);
t_frame			*new_tframe(t_rc_renderer *rend, int height, int width);
int				frame_draw_pixel(t_frame *frame, int x, int y, int color);
int				frame_get_pixel(t_frame *frame, int x, int y);
void			frame_draw_square(t_frame *frame, int x, int y, int size);
t_frame			*frame_resize(t_rc_renderer *rend, t_frame *orig,
				double scaling);
void			frame_clear(t_frame *frame);
int				apply_alpha(int original_color, double alpha);
void			frame_apply_alpha(t_frame *frame, double alpha);
void			frame_delete(t_rc_renderer *rend, t_frame **delete_me);
t_minimap		*new_minimap(t_rc_renderer *rend, t_frame *rc_map, t_vec2i pos,
				double scaling);
void			minimap_add_player(t_minimap *minimap, t_player *player);
void			minimap_set_pos(t_minimap *minimap, t_vec2i pos);
void			minimap_set_alpha(t_minimap *minimap, double transparency);
void			minimap_change_map(t_rc_renderer *rend, t_minimap *mini,
				t_frame *rc_map, double scaling);
void			minimap_draw_ray(t_minimap *minimap, t_vec2d pos,
				double direction, int color);
void			minimap_render(t_rc_renderer *rend, t_minimap *minimap,
				char *window_name);
t_rc_renderer	*new_rc_renderer();
void			add_rcwindow(t_rc_renderer *rend, int height, int width,
				char *title);
void			del_intArr(int **arr, int rows);
int				load_into_list(int fd, t_list **lines, int *max_column_cnt);
void			convert_list2array(t_list *lines, int **arr2d, int rows,
				int columns);
void			**new_2darray(int rows, int columns, size_t element_size);
int				file_is_valid(char *filename);
int				**load_map(char *filename, t_vec2i *row_col);
t_frame			*construct_map(t_rc_renderer *rend, int **array2d,
				int block_size, t_vec2i *row_col);
t_player		*new_player(double x, double y, float direction, double fov);
char			hit_wall(t_frame *map, t_ray *ray, char dir);
double			distance(t_vec2d point_a, t_vec2d point_b);
double			nearest_vertical_hit(t_frame *map, t_ray *ray);
double			nearest_horizontal_hit(t_frame *map, t_ray *ray);
t_ray			construct_ray(t_vec2d position, double direction);
double			cast_ray(t_frame *map, t_vec2d position, double direction,
				int *color);
void			draw_column(t_frame *frame, int col_num, int length, int color);
void			draw_floor_ceiling(t_frame *frame, int floor_color,
				int ceil_color);
void			draw_walls(t_frame *frame, t_frame *rc_map, t_player *player);
void			render_player_window(t_rc_renderer *rend);
void			render_minimap_window( t_rc_renderer *rend);
int				render_loop(void *param);
void			player_translation_controls(int keycode, t_player *player);
void			player_rotation_controls(int keycode, t_player *player);
void			player_fov_controls(int keycode, t_player *player);
void			minimap_delete(t_rc_renderer *rend, t_minimap **minimap);
void			rc_scene_delete(t_rc_renderer *rend, t_rc_scene **scene);
void			windows_delete(t_rc_renderer *rend, t_lmap **windows);
void			rc_renderer_delete(t_rc_renderer **rend);
int				exit_hook(t_rc_renderer *rend);
int				key_hook(int keycode, void *param);
void			hooks(t_rc_renderer *rend);
void			setup_minimap(t_rc_renderer *rend, t_minimap **minimap);

#endif
