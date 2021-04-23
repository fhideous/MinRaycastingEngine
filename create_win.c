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

void	sprite_sort(t_sprites_distns *distns, int size)
{
	int i;
	int j;
	t_sprites_distns tmp;

	i = -1;
	j = -1;
	while (++i < size )
	{
		j = -1;
		while (++j < size - i )
		{
			if (distns[j].dist < distns[j + 1].dist)
			{
				tmp.dist = distns[j].dist;
				tmp.width = distns[j].width;
				tmp.angle = distns[j].angle;
				distns[j] = distns[j + 1];
				distns[j + 1] = tmp;
			}
		}
	}
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

t_sprite_dist_data crossing_sprite(const t_all *all, float angle, const t_texture *txtr, int *hehe)
{
	t_ray	end;
	float	c;
	char	ch;
	t_sprite_dist_data data;

	*hehe = 1;
	c = (float)LEN_STEP;
	end.x = all->plr.x + c * cosf(angle);
	end.y = all->plr.y + c * sinf(angle);
	ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
	[(int)(end.x / (float)txtr->width)];
	while (ch != '1')
	{
		if (ch == '2')
		{
			data.x = end.x;
			data.y = end.y;
			data.dist = c;
			data.angle = angle;
			return data;
		}
		ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
		[(int)(end.x / (float)txtr->width)];
		end.x = all->plr.x + c * cosf(angle);
		end.y  = all->plr.y + c * sinf(angle);
		c += (float)LEN_STEP;
	}
	data.x = -1;
	data.y = -1;
	data.dist = -1;
	data.angle = -1;
	*hehe = -1;
	return  data;
}



void	add_scale_line_sprite(const t_all *all, int n, int hign, const t_texture *textr, int i, t_sprite_dist_data *data)
{
//	int		i;
	float	ratio;
	int		k;
	float	j;
	int		max;

	ratio = (float)hign / (float)textr->width;
	j = 0;
	max = 0;
	if (hign > all->full_map->resolution.y)
	{
		max = (int)((hign - all->full_map->resolution.y)) >> 1;
	}
	while (/*((int)j < all->full_map->resolution.y + max) &&*/
			((int)j < hign + max))
	{
		k = -1;
		while (++k - 1 < (int)ratio)
		{
			if (textr->addr[((int)textr->width * (int)(j / ratio)) + i] == 0)
				continue;
			if(((k + (int)j + (all->full_map->resolution.y >> 1) >= (hign >> 1))) &&
			   (k + (int)j < (hign >> 1) + (all->full_map->resolution.y >> 1)))
			{
				all->full_win.addr[(k + (int)j) * all->full_map->resolution.x + n +
								   all->full_map->resolution.x *
								   ((all->full_map->resolution.y >> 1) - (int)(hign >> 1))]  =
						textr->addr[(((int)textr->width * (int)(j / ratio)) + i)];
			}
		}
		j += (ratio);
	}
}

void	add_sprite_new(t_all *all)
{
	float	angle_start;
	t_sprite_dist_data 	spr_data;
	int		i;
	int		n;
	int		high;
	float	x_y;
	int		k;
	t_sprite_dist_data 	sprite_all_data[1920];
	int		ik;
	int		hehe;
	i = -1;
	x_y = (float)all->full_map->resolution.x / (float)all->full_map->resolution.y;
	while (++i <= all->sprites_loc.size) {
		if (all->sprites_loc.distns->dist < 1)
			continue;
		angle_start = all->sprites_loc.distns[i].angle;
		spr_data = crossing_sprite(all, angle_start, &all->textrs.spite, &hehe);
		n = all->full_map->resolution.x / 2 * (1 + ((angle_start - all->plr.ray.angle) / (M_PI_6)));

//		printf("%f", angle_start - all->plr.ray.angle);
		k = 0;
		while (hehe != -1) {
			sprite_all_data[k] = spr_data;
			angle_start += (M_PI_6 + M_PI_6) / all->full_map->resolution.x;
			spr_data = crossing_sprite(all, angle_start, &all->textrs.spite, &hehe);
			k++;
}
		ik = 0;
		printf("%f %f \n", all->all_distns_1[n], sprite_all_data[0].dist);
//		n = all->full_map->resolution.x / 2 * (1 + ( (sprite_all_data[0].angle - all->plr.ray.angle)/ ( M_PI_6)));

		int n_sprite;
		n_sprite = 0;

		float k_rep0 = (float) k / (float) all->textrs.spite.width;
		float k_rep = k_rep0;
		float k_rep_i = 0;
//		int	sprite_i = 0;
		high = (int) (x_y * (float) all->full_map->resolution.y * (float) all->textrs.spite.width /
					  ABS(sprite_all_data[k / 2].dist));
		while (ik < k && n < all->full_map->resolution.x && n_sprite < all->textrs.spite.width) {
			add_scale_line_sprite(all, n, high, &all->textrs.spite, n_sprite, sprite_all_data);
			ik++;
			k_rep_i++;
			if (k_rep_i >= k_rep) {
				k_rep += k_rep0;
//				k_rep_;
				n_sprite++;
			}
			n++;
		}
	}
}

int     render_next_frame(t_all *all)
{
	add_flour(all);

	sprites_zero(all->sprites_loc.points);
	sprites_dist_sero(all->sprites_loc.distns);
	add_ray(all, &all->full_map->resolution, (float)all->full_map->resolution.x / all->full_map->resolution.y );
	sprite_sort(all->sprites_loc.distns, all->sprites_loc.size);
	add_sprite_new(all);
	do_kek(all);
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
	mlx_loop_hook(all->full_win.mlx, render_next_frame, &all->full_win);

	mlx_hook(all->full_win.win, 2, 1L << 0, key_commands, all);

	mlx_loop(all->full_win.mlx);
}