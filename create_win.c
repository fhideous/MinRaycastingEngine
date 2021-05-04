#include "hdrs/cub3d.h"

void	add_flour(t_all *all)
{
	int		i;
	int		j;
	unsigned int	color_f;
	unsigned int	color_c;

	color_f = (all->f_map->fl_c.R << 16) +
			  (all->f_map->fl_c.G << 8) + all->f_map->fl_c.B;
	color_c = (all->f_map->cl_c.R << 16)
			  + (all->f_map->cl_c.G << 8) + all->f_map->cl_c.B;
	j = (all->f_map->res.y >> 1) * all->f_map->res.x;
	 i = j;
	while (i--)
		all->f_w.addr[i] =color_c;
	i = -1;
	while (++i != j)
		all->f_w.addr[i + j] = color_f;
	mlx_put_image_to_window(all->f_w.mlx, all->f_w.win, all->f_w.img, 0, 0);
}

void	do_kek(t_all *all)
{
	int i;

	i = -1;
	while (++i < all->f_map->res.y)
	{
		all->f_w.addr[i * all->f_map->res.x] = 0;
	}
	i = -1;
	while (++i < all->f_map->res.y)
	{
		all->f_w.addr[1 + i * all->f_map->res.x] = 0;
	}
}

void	distance_to_sprites(t_all *all)
{
	int i;

	i = 0;
	while (i < all->s_spr)
	{
		all->spr_loc[i].dist = hypotf(all->plr.x -
									  (float)all->spr_loc[i].coords.y * (float)all->textrs.n_tex.width - 32,
									  all->plr.y -
									  (float)all->spr_loc[i].coords.x * (float)all->textrs.n_tex.width - 32);
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
	while (i < all->s_spr)
	{
		all->spr_loc[i].angle = atan2f(all->plr.x - (float)(all->textrs.n_tex.width >> 1) -
									   (float)all->spr_loc[i].coords.y * (float)all->textrs.spite.width,
										   all->plr.y - (float)(all->textrs.n_tex.width >> 1) -
										   (float)all->spr_loc[i].coords.x * (float)all->textrs.spite.width);
		{
			all->spr_loc[i].angle += (float)M_PI;
			all->spr_loc[i].angle += (float)(3 * M_PI / 2);
			if(all->spr_loc[i].angle > M_PI + M_PI)
				all->spr_loc[i].angle -= (float)(M_PI + M_PI);
			all->spr_loc[i].angle *= -1;
			all->spr_loc[i].angle += (float)(M_PI + M_PI);
		}
		i++;
	}
}


void		new_iter_sprite(int i, int *sprite_step, float *max, float step)
{
	if (i >= *max)
	{
		*max += step;
		(*sprite_step)++;
	}
}

void		sprite_to_image(t_all *all,  t_point start, int high, int n)
{
	int		i;
	int		j;
	float	ratio_ij[2];
	int		ij_s[2];

	ratio_ij[0] =  (float)high / (float)all->textrs.spite.width;
	if (high > all->f_map->res.y)
		return;
	ij_s[0] = 0;
	i = 0;
	while (i < high)
	{
		if (all->a_d_w[start.x + i] < all->spr_loc[n].dist)
		{
			new_iter_sprite(i++, &ij_s[0], &ratio_ij[0],  (float)high / (float)all->textrs.spite.width);
			continue;
		}
		ij_s[1] = 0;
		j = -1;
		ratio_ij[1] = (float)high / (float)all->textrs.spite.width;
		while (++j < high && start.y + j < all->f_map->res.y)
		{
			if (start.x + i > all->f_map->res.x || start.x + i < 0)
				continue;
			if (all->textrs.spite.addr[ij_s[0] + all->textrs.spite.width * ij_s[1]] != 0x000000)
				all->f_w.addr[start.x + i + (start.y + j) * all->f_map->res.x] =
						all->textrs.spite.addr[ij_s[0] + all->textrs.spite.width * ij_s[1]];
			new_iter_sprite(j, &ij_s[1], &ratio_ij[1],  (float)high / (float)all->textrs.spite.width);
		}
		new_iter_sprite(i++, &ij_s[0], &ratio_ij[0],  (float)high / (float)all->textrs.spite.width);
	}
}

int check_valid_angle(float d_angle, float *angle, float *plr_angle)
{
	if (ABS(*angle - *plr_angle) < M_PI_6 + d_angle )
		return 1;
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

	x_y = (float)all->f_map->res.x / (float)all->f_map->res.y;
	i = -1;
	plr_angle_cpy = all->plr.ray.angle;
	while (++i < all->s_spr)
	{
		high =	(x_y * (float)all->f_map->res.y * (float)all->textrs.spite.width /
				   all->spr_loc[i].dist);
			if (!check_valid_angle((float)high * (float)M_PI_6 /
			(float)all->f_map->res.x, &all->spr_loc[i].angle, &plr_angle_cpy))
			continue;
		start.y = (all->f_map->res.y / 2) - (int)(high / 2);
		start.x = (int)((all->spr_loc[i].angle - plr_angle_cpy) *
						(float)(all->f_map->res.x) / (M_PI_3)) - ((int)high >> 1)
				  + (all->f_map->res.x / 2 );
		sprite_to_image(all, start, (int)high, i);
	}
}

int	render_next_frame(t_all *all)
{
	add_flour(all);
	add_ray(all, &all->f_map->res,
		(float)all->f_map->res.x
		/ (float)all->f_map->res.y);
	distance_to_sprites(all);
	sprite_sort(all->spr_loc, all->s_spr);
	find_angle_sprite(all);
	print_sprite(all);
	do_kek(all);
//
}

int	create_win(t_all *all)
{
	all->f_w.win = mlx_new_window(all->f_w.mlx,
								  all->f_map->res.x,
								  all->f_map->res.y, "cub3d");
	all->f_w.img = mlx_new_image(all->f_w.mlx,
								 all->f_map->res.x, all->f_map->res.y);
	all->f_w.addr = (unsigned int *)mlx_get_data_addr(all->f_w.img,
													  &all->f_w.BPP,
													  &all->f_w.l_len, &all->f_w.endian);
	mlx_hook(all->f_w.win, 2, 1L << 0, key_commands, all);
	if (all->screen)
	{
		render_next_frame(all);
		screenshot(all);
	}
	mlx_loop_hook(all->f_w.mlx, render_next_frame, &all->f_w);
	mlx_loop(all->f_w.mlx);
}
