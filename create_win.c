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

void		find_angle_sprite(t_all *all)
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


void		sprite_to_image(t_all *all,  t_point start, int high, int n)
{
	int i;
	int j;
	float	ratio;
	float	ratio_i;
	float	ratio_j;
	int		i_s;
	int		j_s;

	ratio = (float)high / (float)all->textrs.spite.width;
	ratio_i = ratio;
	if (high > all->full_map->resolution.y)
		return;
	i_s = 0;
//	while (all->sprites_loc[i].dist)
//		i++;
//	i_s = (int)((float)(high - i) / ratio);
	i = 0;
	while (i < high)
	{
		if (all->all_distns_wall[start.x + i] < all->sprites_loc[n].dist)
		{
			i++;
			if (i >= ratio_i)
			{
				ratio_i += ratio;
				i_s++;
			}
			continue;
		}
		j_s = 0;
		j = -1;
		ratio_j = ratio;
		while (++j < high && start.y + j < all->full_map->resolution.y)
		{
			if (start.x + i > all->full_map->resolution.x || start.x + i < 0)
				continue;
			if (all->textrs.spite.addr[i_s + all->textrs.spite.width * j_s] != 0x000000)
				all->full_win.addr[start.x + i + (start.y + j) * all->full_map->resolution.x] =
						all->textrs.spite.addr[i_s + all->textrs.spite.width * j_s];
			if (j >= ratio_j)
			{
				ratio_j += ratio;
				j_s++;
			}
		}
		i++;
		if (i >= ratio_i)
		{
			ratio_i += ratio;
			i_s++;
		}
	}
}

int check_valid_angle(float d_angle, float *angle, float *plr_angle)
{
	if (ABS(*angle - *plr_angle) < M_PI_6 + d_angle )
		return 1;
//	if (plr_angle < 0)
//		return 0;
	if (*angle + *plr_angle > M_PI + M_PI - M_PI_6)
		{
			if (*angle > M_PI + M_PI - M_PI_6 && *plr_angle < M_PI_6)
			{
				*angle -= 2 * M_PI;
				return 1;
			}
			else if (*plr_angle > M_PI + M_PI - M_PI_6 && *angle < M_PI_6)
			{
				*plr_angle -= 2 * M_PI;
				return 1;
			}
		}
	return 0;
}

void print_sprite(t_all *all)
{
	int			i;
	float		high;
	float		x_y;
	t_point		start;
	float		plr_angle_cpy;


	x_y = (float)all->full_map->resolution.x / (float)all->full_map->resolution.y;

	i = -1;

	plr_angle_cpy = all->plr.ray.angle;
	while (++i < all->size_sprites)
	{
		high =	(x_y * (float) all->full_map->resolution.y * (float) all->textrs.spite.width /
				   all->sprites_loc[i].dist);
			if (!check_valid_angle((float)high * (float)M_PI_6 / (float)all->full_map->resolution.x, &all->sprites_loc[i].angle, &plr_angle_cpy)) {
			continue;
		}
		start.y = (all->full_map->resolution.y / 2) - (int)(high/ 2);
		start.x = (int)((all->sprites_loc[i].angle - plr_angle_cpy) * (float)(all->full_map->resolution.x) / (M_PI_3)) - ((int)high >> 1) + (all->full_map->resolution.x /2 );
		sprite_to_image(all, start, (int)high, i);
	}
}

int     render_next_frame(t_all *all)
{
	add_flour(all);

	add_ray(all, &all->full_map->resolution, (float)all->full_map->resolution.x / (float)all->full_map->resolution.y);
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
	all->full_win.addr = (unsigned int*)mlx_get_data_addr(all->full_win.img,
										   &all->full_win.bits_per_pixel,
										   &all->full_win.line_length,
										   &all->full_win.endian);
	mlx_hook(all->full_win.win, 2, 1L << 0, key_commands, all);
	mlx_loop_hook(all->full_win.mlx, render_next_frame, &all->full_win);

	mlx_loop(all->full_win.mlx);
}
