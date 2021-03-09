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
			my_mlx_pixel_put(all->full_win, i + all->plr.x - SCALE / 2,
					j + all->plr.y -SCALE / 2, color);

	mlx_put_image_to_window(all->full_win->mlx,
							all->full_win->win, all->full_win->img, 0, 0);
}

add_flour(t_all *all)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i != all->full_map->resolution.x)
	{
		while(++j != all->full_map->resolution.y / 2)
			my_mlx_pixel_put(all->full_win, i , j, 0xE3CC87);
		j = -1;
	}
	i = -1;
	j = all->full_map->resolution.y / 2 - 1;
	while (++i != all->full_map->resolution.x)
	{
		while(++j != all->full_map->resolution.y)
			my_mlx_pixel_put(all->full_win, i , j,  0xE3D29F);
		j = all->full_map->resolution.y / 2  -1 ;
	}


	mlx_put_image_to_window(all->full_win->mlx, all->full_win->win, all->full_win->img, 0, 0);

}


int     render_next_frame(t_all *all)
{
	mlx_destroy_image(all->full_win->mlx, all->full_win->img);

	all->full_win->img = mlx_new_image(all->full_win->mlx,
									all->full_map->resolution.x,
							 all->full_map->resolution.y);
	all->full_win->addr = mlx_get_data_addr(all->full_win->img,
								  &all->full_win->bits_per_pixel,
								  &all->full_win->line_length,
								  &all->full_win->endian);

//	add_plr(all);
//	scene_put(all, all->full_map);
	add_flour(all);
	add_ray(all, &all->full_map->resolution);

}

int		render_plr_frame(t_all *all)
{
	add_plr(all);
//	add_ray(all, res);
}

int	create_win(t_cub_map full_map, t_all all)
{
	void *mlx;
	t_win 	*win;

	win = malloc(sizeof(t_win));
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, full_map.resolution.x,
								  full_map.resolution.y, "cub3d");
	win->img = mlx_new_image(win->mlx, full_map.resolution.x,
							 full_map.resolution.y);
	win->addr = mlx_get_data_addr(win->img,
								  &win->bits_per_pixel,
								  &win->line_length,
								  &win->endian);
	all.full_map = &full_map;
	all.full_win = win;
//	render_next_frame(&all, &full_map);
	mlx_loop_hook(all.full_win->mlx, render_next_frame, &all.full_win);

	mlx_hook(all.full_win->win, 2, 1L << 0, key_commands, &all);
//	render_next_frame(&all);

	mlx_loop(all.full_win->mlx);
	free(win);

}