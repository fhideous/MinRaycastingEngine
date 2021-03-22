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

	for(int j = 0; j < SCALE / 4; j++)
		for (int i = 0; i < SCALE /4; i++)
			my_mlx_pixel_put(all->full_win, i + all->plr.x - SCALE / 4 / 2,
					j + all->plr.y - SCALE / 4 / 2, color);

	mlx_put_image_to_window(all->full_win->mlx,
							all->full_win->win, all->full_win->img, 0, 0);
}

void add_flour(t_all *all)
{
	int i;
	int j;

	j = (all->full_map->resolution.y >> 1) * all->full_map->resolution.x;
	 i = j;
	while (i--)
			all->full_win->addr[i] = 0xE3CC87;
	i = -1;
	while (++i != j)
		all->full_win->addr[i + j] = 0xE3D29F;
	mlx_put_image_to_window(all->full_win->mlx, all->full_win->win, all->full_win->img, 0, 0);

}

void	scale_texture(t_all *all)
{

}

int     render_next_frame(t_all *all)
{
//	mlx_destroy_image(all->full_win->mlx, all->full_win->img);
//
//	all->full_win->img = mlx_new_image(all->full_win->mlx,
//									all->full_map->resolution.x,
//							 all->full_map->resolution.y);
//	all->full_win->addr = mlx_get_data_addr(all->full_win->img,
//								  &all->full_win->bits_per_pixel,
//								  &all->full_win->line_length,
//								  &all->full_win->endian);


	add_flour(all);

//	scale_texture(all);

	add_ray(all, &all->full_map->resolution);

}


int	create_win(t_all *all)
{
//	t_win 	*win;

//	win = malloc(sizeof(t_win));
	all->full_win->win = mlx_new_window(all->full_win->mlx, all->full_map->resolution.x,
								  all->full_map->resolution.y, "cub3d");

	all->full_win->img = mlx_new_image(all->full_win->mlx, all->full_map->resolution.x,
							 all->full_map->resolution.y);
	all->full_win->addr = mlx_get_data_addr(all->full_win->img,
								  &all->full_win->bits_per_pixel,
								  &all->full_win->line_length,
								  &all->full_win->endian);
//	all->full_win = win;
//	render_next_frame(&all, &full_map);
	mlx_loop_hook(all->full_win->mlx, render_next_frame, &all->full_win);

	mlx_hook(all->full_win->win, 2, 1L << 0, key_commands, all);
//	render_next_frame(&all);

	mlx_loop(all->full_win->mlx);
}