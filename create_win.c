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
	data.x = end.x;
	data.y = end.y;
	data.dist = c;
	data.angle = angle;
	*hehe = -1;
	return  data;
}

float check_sprite_angle(const t_all *all, float angle, const t_texture *txtr)
{
	t_ray	end;
	float	c;
	char	ch;

	c = (float)LEN_STEP;
	end.x = all->plr.x + c * cosf(angle);
	end.y = all->plr.y + c * sinf(angle);
	ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
	[(int)(end.x / (float)txtr->width)];
	while (ch != '2')
	{
		if (end.y < all->textrs.n_tex.width || end.x < all->textrs.n_tex.width ||
		(end.y / (float)txtr->width) >= ft_strlen(all->full_map->map[0]) ||
		(end.x / (float)txtr->width) >= ft_strlen(all->full_map->map[0]))
		{
			return -1;
		}
		ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
		[(int)(end.x / (float)txtr->width)];
		end.x = all->plr.x + c * cosf(angle);
		end.y  = all->plr.y + c * sinf(angle);
		c += (float)LEN_STEP;
	}
	return  c;
}

void	add_scale_line_sprite(const t_all *all, int n, int hign, const t_texture *textr, int i)
{
	float	ratio;
	int		k;
	float	j;
	int		max;
	int		step;

	step = 0;
//	while (data->dist > )

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

			if (((int)textr->width * (int)(j / ratio)) + i > all->textrs.spite.width * all->textrs.spite.width)
				continue;
			if (textr->addr[((int)textr->width * (int)(j / ratio)) + i] == 0) {
				continue;
			}
			if(((k + (int)j + (all->full_map->resolution.y >> 1) >= (hign >> 1))) &&
			   (k + (int)j < (hign >> 1) + (all->full_map->resolution.y >> 1)))
//			if ((((int)textr->width * (int)(j / ratio)) + i + (int)((float)(hign - k_k) / ratio)) <= all->textrs.spite.width )
			{
				all->full_win.addr[(k + (int)j) * all->full_map->resolution.x + n +
								   all->full_map->resolution.x *
								   ((all->full_map->resolution.y >> 1) - (int)(hign >> 1))]  =
						textr->addr[(((int)textr->width * (int)(j / ratio)) + i/* + (int)((float)(hign - k_k) / ratio)*/)];
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

void	add_sprite_new(t_all *all)
{
	float	angle_start;
	t_sprite_dist_data 	spr_data;
	int		i;
	int		n;
	float		high;
	float	x_y;
//	int		k;
	t_sprite_dist_data 	sprite_all_data[1920];
	float 				sprites_dist_full[1920];
	int		ik;
	int		hehe;

	i = -1;
	while (++i < 1920)
		sprites_dist_full[i] = 0;
	i = -1;
	x_y = (float)all->full_map->resolution.x / (float)all->full_map->resolution.y;
	while (++i <= all->sprites_loc.size)
	{
		sprite_all_data_zero(sprite_all_data);
		if (all->sprites_loc.distns[i].dist < all->textrs.n_tex.width)
			continue;
		angle_start = all->sprites_loc.distns[i].angle;
		float n_d_alpha = 0;
		float sprite_dist_full;

		sprite_dist_full = check_sprite_angle(all, angle_start - M_PI_3 / all->full_map->resolution.x, &all->textrs.n_tex) ;

		i = 0;
		while (sprite_dist_full != -1)
		{
			sprites_dist_full[i] = sprite_dist_full;
			n_d_alpha += M_PI_3 / all->full_map->resolution.x;
			sprite_dist_full = check_sprite_angle(all, angle_start - n_d_alpha , &all->textrs.n_tex) ;
			i++;
		}
		i = 0;
		n = all->full_map->resolution.x / 2 * (1 + ((angle_start - all->plr.ray.angle - n_d_alpha) / (M_PI_6)));
		spr_data = crossing_sprite(all, angle_start - n_d_alpha, &all->textrs.spite, &hehe);
		int k = 0;
		float n_d_alpha_max = n_d_alpha;
		while (hehe != -1  || n_d_alpha > 0){
			sprite_all_data[k] = spr_data;
			k++;
			angle_start += (M_PI_6 + M_PI_6) / all->full_map->resolution.x;
			spr_data = crossing_sprite(all, angle_start - n_d_alpha_max, &all->textrs.spite, &hehe);
			n_d_alpha -= M_PI_3 / all->full_map->resolution.x;
		}
		ik = 0;

//		n = all->full_map->resolution.x / 2 * (1 + ( (sprite_all_data[0].angle - all->plr.ray.angle)/ ( M_PI_6)));

//		printf("%d\t%d\t%d\n", high, k, high - k);
		int n_sprite;
		n_sprite = 0;

		float	dist_for_high;

		if (sprites_dist_full[k / 2] > 0) {
			dist_for_high =  sprites_dist_full[k / 2];
		}
		else {
			dist_for_high = sprite_all_data[(int)(k / 2)].dist;
		}
		printf("%f\t%f\n", sprite_all_data[(int)(k / 2)].dist, sprites_dist_full[0]);

		high =  (x_y * (float) all->full_map->resolution.y * (float) all->textrs.spite.width /
					  ABS(dist_for_high));
		float k_rep0 = (float) high / (float)all->textrs.spite.width;
		float k_rep = k_rep0;
		float k_rep_i = 0;
//		int	sprite_i = 0;
		while (ik < k && n < all->full_map->resolution.x && n_sprite < all->textrs.spite.width) {
			if (sprite_all_data[ik].dist >= sprites_dist_full[ik] && n > 0) {
				add_scale_line_sprite(all, n, (int)high, &all->textrs.spite, n_sprite);
			}
			ik++;
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
		dx = - (all->plr.x - all->textrs.n_tex.width / 2) / all->textrs.n_tex.width + (float)all->sprts_crds.coordints[i].y ;
		dy = - (all->plr.y - all->textrs.n_tex.width / 2) / all->textrs.n_tex.width + (float)all->sprts_crds.coordints[i].x;

//		if(dx > 0 && dy >= 0)
//		angle = atanf((float)dy / (float)dx );
//			if (dx == 0)
//				angle =0;
//			while(angle > M_PI_3)
//				angle-= M_PI_6;
//		while(angle < -M_PI_3)
//			angle += M_PI_6;
//		else if (dx < 0 && dy >= 0)
			angle = M_PI - atanf((float)dy / (float)dx);
//		else if (dx < 0 && dy < 0)
//			angle = M_PI + atanf((float)dy / (float)dx);
//		else if (dx > 0 && dy < 0)
//			angle = M_PI + M_PI - atanf((float)dy / (float)dx);
//		else if (dx == 0 && dy > 0)
//			angle = M_PI_2;
//		else if (dx == 0 && dy < 0)
//			angle = M_PI_2 + M_PI_2 + M_PI_2;
		all->sprites_loc.angle_sprite_start[i] = angle - plr_angle;
//		all->sprites_loc.angle_sprite_start[i] = fmod(all->sprites_loc.angle_sprite_start[i], M_PI_3);
		i++;
	}
}

int     render_next_frame(t_all *all)
{
	add_flour(all);

	sprites_zero(all->sprites_loc.points);
	sprites_dist_sero(all->sprites_loc.distns);
	add_ray(all, &all->full_map->resolution, (float)all->full_map->resolution.x / all->full_map->resolution.y);
	sprite_sort(all->sprites_loc.distns, all->sprites_loc.size);
	find_angle_sprites(all);
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