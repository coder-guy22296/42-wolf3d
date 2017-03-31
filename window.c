#include "wolf3d.h"

void	add_rcwindow(t_rc_renderer *rend, int height, int width, char *title)
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

void	*get_rcwindow(t_rc_renderer *rend, char *window_name)
{
	t_lmap	*element;
	void	*window;

	element = ft_lmapget(rend->windows, window_name);
	window = *((void **)element->content);
	return (window);
}

void	windows_delete(t_rc_renderer *rend, t_lmap **windows)
{
	t_lmap	*cur;
	t_lmap	*last;

	cur = *windows;
	while (cur)
	{
		ft_strdel((char **)&cur->key);
		mlx_destroy_window(rend->mlx, *((void **)cur->content));
		ft_memdel(&cur->content);
		last = cur;
		cur = cur->next;
		ft_memdel((void **)&last);
	}
	*windows = NULL;
}
