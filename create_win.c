#include "hdrs/cub3d.h"
#include <math.h>

void add_flour(t_all *all)
{
	int i;
	int j;
	unsigned int color_f;
	unsigned int color_c;

	color_f = (all->full_map->fl_color.R << 16) + (all->full_map->fl_color.G << 8) + all->full_map->fl_color.B;
	color_c = (all->full_map->cel_color.R << 16) + (all->full_map->cel_color.G << 8) + all->full_map->cel_color.B;
	j = (all->full_map->resolution.y >> 1) * all->full_map->resolution.x;
	 i = j;
	while (i--)
			all->full_win.addr[i] =color_c;
	i = -1;
	while (++i != j)
		all->full_win.addr[i + j] = color_f;
	mlx_put_image_to_window(all->full_win.mlx, all->full_win.win, all->full_win.img, 0, 0);
}

void	do_kek(t_all *all)
{
	int i;

	i = -1;
	while (++i < all->full_map->resolution.y)
	{
		all->full_win.addr[i * all->full_map->resolution.x] = 0;
	}
	i = -1;
	while (++i < all->full_map->resolution.y)
	{
		all->full_win.addr[1 + i * all->full_map->resolution.x] = 0;
	}
}

void	distance_to_sprites(t_all *all)
{
	int i;

	i = 0;
	while (i < all->size_sprites)
	{
		all->sprites_loc[i].dist = hypotf(all->plr.x -
				(float)all->sprites_loc[i].coords.y * (float)all->textrs.n_tex.width - 32,
				all->plr.y -
				(float)all->sprites_loc[i].coords.x * (float)all->textrs.n_tex.width - 32);
		i++;
	}
}



void	sprite_sort(t_sprite *sprs_CDA, int size)
{
	int i;
	int j;
	t_sprite tmp;

	i = -1;
	j = -1;
	while (++i < size )
	{
		j = -1;
		while (++j < size - i )
		{
			if (sprs_CDA[j].dist < sprs_CDA[j + 1].dist)
			{
				tmp.dist = sprs_CDA[j].dist;
				tmp.coords = sprs_CDA[j].coords;
				tmp.angle = sprs_CDA[j].angle;
				sprs_CDA[j] = sprs_CDA[j + 1];
				sprs_CDA[j + 1] = tmp;
			}
		}
	}
}

void find_angle_sprite(t_all *all)
{
	int i;

	i = 0;
	while (i < all->size_sprites)
	{
		all->sprites_loc[i].angle = atan2f(all->plr.x - (float)(all->textrs.n_tex.width >> 1) -
										   (float)all->sprites_loc[i].coords.y * (float)all->textrs.spite.width,
										   all->plr.y - (float)(all->textrs.n_tex.width >> 1) -
										   (float)all->sprites_loc[i].coords.x * (float)all->textrs.spite.width);
{
		all->sprites_loc[i].angle += (float)M_PI;
		all->sprites_loc[i].angle += (float)(3 * M_PI / 2);
		if(all->sprites_loc[i].angle > M_PI + M_PI)
			all->sprites_loc[i].angle -= (float)(M_PI + M_PI);
		all->sprites_loc[i].angle *= -1;
		all->sprites_loc[i].angle += (float)(M_PI + M_PI);
}
		i++;
	}
}

void sprite_to_image(t_all *all,  t_point start, int high, int n)
{
	int i;
	int j;
	i = 0;


	if (high > all->full_map->resolution.y)
//		high = all->full_map->resolution.y;
			return;
	while (i < high)
	{
		j = -1;
		if (all->all_distns_wall[start.x + i] < all->sprites_loc[n].dist)
		{
			i++;
			continue;
		}
		while (++j < high && start.y + j < all->full_map->resolution.y)
		{
			if (start.x + i > all->full_map->resolution.x || start.x + i < 0)
				continue;
			all->full_win.addr[start.x + i + (start.y + j) * all->full_map->resolution.x] = all->textrs.spite.addr[i + 32 * j];
		}
		i++;
	}
}

void print_sprite(t_all *all)
{
	int			i;
	float		high;
	float		x_y;
	t_point		start;
	float		plr_angle;

	i = -1;
	x_y = (float)all->full_map->resolution.x / (float)all->full_map->resolution.y;
	plr_angle = all->plr.ray.angle;

	i = -1;

	while (++i < all->size_sprites)
	{

		high =	(x_y * (float) all->full_map->resolution.y * (float) all->textrs.spite.width /
				   all->sprites_loc[i].dist);
		if (ABS(all->sprites_loc[i].angle - all->plr.ray.angle) > M_PI_6 + (float)high * M_PI_6 / (float)all->full_map->resolution.x /*&&
				ABS(all->sprites_loc[i].angle - all->plr.ray.angle) < M_PI + M_PI - M_PI_6*/) {
			continue;
		}
//		printf("%d\t%d\n", (int)(57.295779513* all->sprites_loc[i].angle),(int)(57.295779513* all->plr.ray.angle));

		start.y = (all->full_map->resolution.y / 2) - (int)(high/ 2);
//		while ((all->sprites_loc[i].angle - all->plr.ray.angle) > M_PI_6)
//			all->sprites_loc[i].angle -= M_PI_3;
		start.x = (int)((all->sprites_loc[i].angle - all->plr.ray.angle) * (float)(all->full_map->resolution.x) / (M_PI_3)) - ((int)high >> 1) + (all->full_map->resolution.x /2 );

		sprite_to_image(all, start, (int)high, i);
	}
}

int     render_next_frame(t_all *all)
{
	add_flour(all);

	add_ray(all, &all->full_map->resolution, (float)all->full_map->resolution.x / all->full_map->resolution.y);
	distance_to_sprites(all);
	sprite_sort(all->sprites_loc, all->size_sprites);
	find_angle_sprite(all);
	print_sprite(all);
	do_kek(all);
//	screenshot(all);
}

int	create_win(t_all *all)
{
	all->full_win.win = mlx_new_window(all->full_win.mlx, all->full_map->resolution.x,
									   all->full_map->resolution.y, "cub3d");

	all->full_win.img = mlx_new_image(all->full_win.mlx, all->full_map->resolution.x,
									  all->full_map->resolution.y);
	all->full_win.addr = mlx_get_data_addr(all->full_win.img,
										   &all->full_win.bits_per_pixel,
										   &all->full_win.line_length,
										   &all->full_win.endian);
	mlx_hook(all->full_win.win, 2, 1L << 0, key_commands, all);
	mlx_loop_hook(all->full_win.mlx, render_next_frame, &all->full_win);

	mlx_loop(all->full_win.mlx);
}
