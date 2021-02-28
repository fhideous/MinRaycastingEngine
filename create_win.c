#include "hdrs/cub3d.h"
#include <math.h>

void            my_mlx_pixel_put(t_win *data, int x, int y,unsigned int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		add_plr(t_all *all)
{
	static int color = 0xFC69900;
	static int cnt = 0;
	static int i = 1;

	for(int j = 0; j < SCALE; j++)
		for (int i = 0; i < SCALE; i++)
			my_mlx_pixel_put(all->full_win, i + all->plr.x * SCALE,
					j + all->plr.y * SCALE, color);

	mlx_put_image_to_window(all->full_win->mlx,
							all->full_win->win, all->full_win->img, 0, 0);
}


int     render_next_frame(t_all *all, t_cub_map *full_map)
{
	double angle;
	scene_put(all, full_map);
	add_plr(all);
	add_ray(all);
}

int	create_win(t_cub_map full_map, t_all all)
{
	void *mlx;
	t_win 	*win;

	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, full_map.resolution.x,
								  full_map.resolution.y, "cub3d");
	win->img = mlx_new_image(win->mlx, full_map.resolution.x,
								 full_map.resolution.y);
	win->addr = mlx_get_data_addr(win->img,
									  &win->bits_per_pixel,
									  &win->line_length,
									  &win->endian);
	all.full_win = win;
	render_next_frame(&all, &full_map);
//	mlx_loop_hook(allfull_win.mlx, render_next_frame, &allfull_win);
	mlx_loop(all.full_win->mlx);
}