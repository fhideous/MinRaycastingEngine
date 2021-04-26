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
		c += (float)LEN_STEP ;
//		if (c >= 300)
//			c++;
	}
	data.x = end.x;
	data.y = end.y;
	data.dist = c;
	data.angle = angle;
	*hehe = -1;
	return  data;
}

float check_sprite_angle(const t_all *all, float angle, const t_texture *txtr, const t_ray *sprite)
{
	t_ray	end;
	float	c;
	char	ch;

	c = (float)LEN_STEP;
	end.x = all->plr.x + c * cosf(angle);
	end.y = all->plr.y + c * sinf(angle);
	ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
	[(int)(end.x / (float)txtr->width)];
	int fas= ft_strlen(all->full_map->map[0]);
	while (ch != '2')
	{
		if (c - sprite->len > txtr->width)
		{
			return -1;
		}
		c += (float)LEN_STEP;
		end.x = all->plr.x + c * cosf(angle);
		end.y  = all->plr.y + c * sinf(angle);
		ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
		[(int)(end.x / (float)txtr->width)];
//		if ((int)(end.x / txtr->width) == 16)
//		{c++; c--;}
//		if ((int)(end.y / txtr->width) == 6)
//		{c++; c--;}
	}
	return  c;
}

void	add_scale_line_sprite(const t_all *all, int n, int hign, const t_texture *textr, int i)
{
	float	ratio;
	int		k;
	float	j;
	int		max;

	ratio = (float)hign / (float)textr->width;
	j = 0;
	max = 0;
	if (hign > all->full_map->resolution.y)
	{
//		return;
		hign = all->full_map->resolution.y;
		max = (int)((hign - all->full_map->resolution.y)) >> 1;
	}
	while ((int)j < hign + max)
	{
		k = -1;
		while (++k - 1 < (int)ratio)
		{

			if (((int)textr->width * (int)(j / ratio)) + i > all->textrs.spite.width * all->textrs.spite.width)
				continue;
//			if (textr->addr[((int)textr->width * (int)(j / ratio)) + i] == 0)
//				continue;
			if(((k + (int)j + (all->full_map->resolution.y >> 1) >= (hign >> 2))) &&
			   (k + (int)j < (hign >> 1) + (all->full_map->resolution.y >> 1)))
			{
				all->full_win.addr[(k + (int)j) * all->full_map->resolution.x + n +
								   all->full_map->resolution.x *
								   (max + (all->full_map->resolution.y >> 1) - (int)(hign >> 1))]  =
						textr->addr[(((int)textr->width * (int)(j  / ratio)) + i)];
			}
		}
		j += (ratio);
	}
}

void sprite_all_data_zero(t_sprite_dist_data *data)
{
	int i;
	t_sprite_dist_data tmp;
	tmp.dist = 0;
	tmp.y = 0;
	tmp.x = 0;
	tmp.angle = 0;

	i = 0;
	while (i < 1920)
	{
		data[i] = tmp;
		i++;
	}
}

int 	sprite_find(const t_all *all, t_ray *point, float angle)
{
	t_ray end;
	float c;
	char ch;

	c = (float)LEN_STEP;
	end.x = all->plr.x + c * cosf(angle);
	end.y = all->plr.y + c * sinf(angle);
	ch = all->full_map->map[(int)(end.y / all->textrs.n_tex.width)]
			[(int)(end.x) / all->textrs.n_tex.width];

	while (ch != '2')
	{
		if (/*end.y < all->textrs.n_tex.width || end.x < all->textrs.n_tex.width ||*/
	(end.y / all->textrs.n_tex.width) >= ft_strlen(all->full_map->map[0]) ||
	(end.x / all->textrs.n_tex.width) >= ft_strlen(all->full_map->map[0]))
		{
			return -1;
		}
		c += (float)LEN_STEP;
		end.x = all->plr.x + c * cosf(angle);
		end.y = all->plr.y + c * sinf(angle);
		ch = all->full_map->map[(int)(end.y / all->textrs.n_tex.width)]
		[(int)(end.x) / all->textrs.n_tex.width];
	}

	point->x = (float)(int)(end.x / all->textrs.n_tex.width);
	point->y = (float)(int)(end.y / all->textrs.n_tex.width);
	point->len = c;
}

void	add_sprite_new(t_all *all)
{
	float	angle_start;
	t_sprite_dist_data 	spr_data;
	int		i;
	int		n;
	float	high;
	float	x_y;
//	int		k;
	t_sprite_dist_data 	sprite_all_data[1920];
	float 				sprites_dist_full[1920];
	int		ik;
	int		hehe;
	int		j;
	i = -1;
	x_y = (float)all->full_map->resolution.x / (float)all->full_map->resolution.y;
	while (++i < all->sprites_loc.size)
	{
		while (++j < 1920) {
			sprites_dist_full[j] = 0;
		}
		sprite_all_data_zero(sprite_all_data);
		if (all->sprites_loc.distns[i].dist < all->textrs.n_tex.width - (all->textrs.n_tex.width >> 2))
			continue;
		angle_start = all->sprites_loc.distns[/*all->sprites_loc.size -*/ i].angle;
		float n_d_alpha = M_PI_3 / all->full_map->resolution.x;
		float sprite_dist_full;
		t_ray sprite;
		sprite_find(all, &sprite, angle_start);
		sprite_dist_full = check_sprite_angle(all, angle_start - M_PI_3 / all->full_map->resolution.x, &all->textrs.n_tex, &sprite) ;

		j = 0;
		while (sprite_dist_full != -1 && j < 1920)
		{
//			if (sprite_dist_full)
			sprites_dist_full[j] = sprite_dist_full;
			n_d_alpha += M_PI_3 / all->full_map->resolution.x;
			sprite_dist_full = check_sprite_angle(all, angle_start - n_d_alpha , &all->textrs.n_tex, &sprite) ;
			j++;
		}
		j = 0;
		n = all->full_map->resolution.x / 2 * (1 + ((angle_start - all->plr.ray.angle - n_d_alpha) / (M_PI_6)));
		spr_data = crossing_sprite(all, angle_start - n_d_alpha, &all->textrs.spite, &hehe);
		int k = 0;
		float n_d_alpha_max = n_d_alpha;
		while ((hehe != -1  || n_d_alpha > 0) && k < 1920){
			sprite_all_data[k] = spr_data;
			k++;
			angle_start += (M_PI_6 + M_PI_6) / all->full_map->resolution.x;
			spr_data = crossing_sprite(all, angle_start - n_d_alpha_max, &all->textrs.spite, &hehe);
			n_d_alpha -= M_PI_3 / all->full_map->resolution.x;
		}
		ik = 0;

		int n_sprite;
		n_sprite = 0;

		float	dist_for_high;
//		if (angle_start > M_PI_6)
//			j = 0;
//		else
//			j  = k;
//		printf("%d\n",k);
		dist_for_high = sprite_all_data[(int)(k -1) /2  ].dist +  sprite_all_data[(int)(k -1) /4 ].dist
				+ sprite_all_data[(int)((3 * k) / 4)].dist /*+ sprite_all_data[(int)  (k -1) /8 ].dist*/;
		dist_for_high /= 3;
//		dist_for_high = sprite_all_data[1].dist;
//		if (sprites_dist_full[ik - 1] != 0)
//			dist_for_high = sprites_dist_fulll[ik];
//		printf("%d", k);
		printf("%d\t%f\n", k, sprite_all_data[(int)(k -1) /2  ].dist);
//		dist_for_high = sprite_all_data[(int) ((k - 1))].dist;
		high =  (x_y * (float) all->full_map->resolution.y * (float) all->textrs.spite.width /
				 ABS(dist_for_high));
//		printf("%f\t\n",high);
		float k_rep0 = (float) high / (float)all->textrs.spite.width;
		float k_rep = k_rep0;
		float k_rep_i = 0;
		j = -1;

		while (sprites_dist_full[j + 1] != 0)
		{
			j++;
			//			k_cpy += k_rep;
		}
//		n_sprite += (int)((float)(j) * ((float)(k + j) / (float)all->textrs.spite.width));
//		printf("kek %d\t%d\t%d\n", j, k, j+k);
//		n_sprite += (k - j);

		n_d_alpha = 0;
		float k_angle;
		while (ik <= k && n < all->full_map->resolution.x && n_sprite < all->textrs.spite.width) {
			if ( n > 0 && (/* sprite_all_data[ik].dist >= sprites_dist_full[0] */
							sprites_dist_full[ik] == 0)) {

//				printf("%f\t%f\n", sprite_all_data[0].dist, sprites_dist_full[0] );
				k_angle = cosf( n_d_alpha);
				if (k_angle == 0)
				k_angle = 1;
//					high =  (x_y * (float) all->full_map->resolution.y * (float) all->textrs.spite.width /
//							 ABS(sprite_all_data[ik].dist * k_angle));
				add_scale_line_sprite(all, n, (int)high, &all->textrs.spite, n_sprite);
			n_d_alpha += M_PI_3 / all->full_map->resolution.x;

			}
			ik++;
//			printf("%f\n", high);
			k_rep_i++;
			if (k_rep_i >= k_rep) {
				k_rep += k_rep0;
				n_sprite++;
			}
			n++;

		}
	}
}

void 	find_angle_sprites(t_all *all)
{
	float	dx;
	float	dy;
	float	angle;
	int		i;
	float	plr_angle;

	plr_angle = all->plr.ray.angle;
	i = -1;
	while (++i <= SPRITES_MAX)
		all->sprites_loc.angle_sprite_start[i] = 0;
	i = 0;
	while (i <= all->sprites_loc.size)
	{
		dx = - (all->plr.x - all->textrs.n_tex.width / 2) / all->textrs.n_tex.width + (float)all->sprites_loc.points[i].y ;
		dy = - (all->plr.y - all->textrs.n_tex.width / 2) / all->textrs.n_tex.width + (float)all->sprites_loc.points[i].x;
		angle = M_PI - atanf((float)dy / (float)dx);
		all->sprites_loc.angle_sprite_start[i] = angle - plr_angle;
		i++;
	}
}

int     render_next_frame(t_all *all)
{
	add_flour(all);

//	sprites_zero(all->sprites_loc.points);
	sprites_dist_sero(all->sprites_loc.distns);
	add_ray(all, &all->full_map->resolution, (float)all->full_map->resolution.x / all->full_map->resolution.y);
	sprite_sort(all->sprites_loc.distns, all->sprites_loc.size);
	find_angle_sprites(all);
	add_sprite_new(all);
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
	mlx_loop_hook(all->full_win.mlx, render_next_frame, &all->full_win);

	mlx_hook(all->full_win.win, 2, 1L << 0, key_commands, all);

	mlx_loop(all->full_win.mlx);
}
