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
#define M_PI_3 1.047197551
#define M_PI_6 0.523598776
#define M_PI_12 0.261799388
int find_i(const t_all *all, int n)
{
	float xd;
	float yd;

	int i;
	xd = (all->plr.x - all->sprites_loc.coords->x);
	yd = (all->plr.y - all->sprites_loc.coords->y);

	if (ABS(xd) > ABS(yd))
		return 1;
	else
		return 0;
	/*
	int	sign_x;
	int	sign_y;

	if (xd > 0)
		sign_y = -1;
	else
		sign_y = 1;
	if (yd > 0)
		sign_x = 1;
	else
		sign_x = -1;
	i  = sign_x * (all->sprites_loc.coords[n].x) % all->textrs.spite.width
		 + (sign_y * (all->sprites_loc.coords[n].y ) % all->textrs.spite.width);
*/


//	if (ABS(yd) > ABS(xd))
//	{
//		if (yd > 0)
//			i  = (all->sprites_loc.coords[n].x + (all->textrs.spite.width / 2)) % all->textrs.spite.width;
//		else
//			i  = -(all->sprites_loc.coords[n].x + (all->textrs.spite.width / 2)) % all->textrs.spite.width;

//	}
//	else if (xd > 0)
//		i  = -((all->sprites_loc.coords[n].y + (all->textrs.spite.width / 2)) % all->textrs.spite.width);
//	else
//		i  = ((all->sprites_loc.coords[n].y + (all->textrs.spite.width / 2)) % all->textrs.spite.width);
	/*

	if (all->plr.ray.angle >= M_PI_3 && all->plr.ray.angle < M_PI_3 + M_PI_3)
		i  = -((all->sprites_loc.coords[n].x + (all->textrs.spite.width / 2)) % all->textrs.spite.width);
	else if (all->plr.ray.angle >= (M_PI_6) + M_PI_3 + M_PI_3 && all->plr.ray.angle <= M_PI_6 + M_PI_3 + M_PI_3 + M_PI_3)
		i  = -((all->sprites_loc.coords[n].y - (all->textrs.spite.width / 2)) % all->textrs.spite.width);
	else if (all->plr.ray.angle >= (M_PI_3) + M_PI_3 + M_PI_3 + M_PI_3&& all->plr.ray.angle <= M_PI_3 + M_PI_3 + M_PI_3 + M_PI_3 + M_PI_3)
		i  = (all->sprites_loc.coords[n].x + (all->textrs.spite.width / 2)) % all->textrs.spite.width;
	else if (all->plr.ray.angle <= M_PI_6 ||
			 (all->plr.ray.angle >= M_PI + M_PI - M_PI_6))
		i  = (all->sprites_loc.coords[n].y - (all->textrs.spite.width / 2)) % all->textrs.spite.width;
	else if (all->plr.ray.angle <= M_PI_6 )
		i  = (all->sprites_loc.coords[n].y - all->sprites_loc.coords[n].x) % all->textrs.spite.width;
	else
//	i = -1;
		i  = ABS(all->sprites_loc.coords[n].y - all->sprites_loc.coords[n].x) % all->textrs.spite.width +
		 ABS(all->sprites_loc.coords[n].x + (all->sprites_loc.coords[n].y / 2)) % all->textrs.spite.width;
*/

	//	if (all->plr.ray.angle > M_PI_4 && all->plr.ray.angle < M_PI_4 + M_PI_2)
//			i  = -(all->sprites_loc.coords[n].x - (all->textrs.spite.width / 2)) % all->textrs.spite.width;
//	else if (all->plr.ray.angle > M_PI_4 + M_PI_2 && all->plr.ray.angle < M_PI_4 + M_PI_2 + M_PI_2)
//			i  = -(all->sprites_loc.coords[n].y - (all->textrs.spite.width / 2)) % all->textrs.spite.width;
//	else if (all->plr.ray.angle > M_PI_4 + M_PI_2  + M_PI_2 && all->plr.ray.angle < M_PI_4 + M_PI_2 + M_PI_2 + M_PI_2)
//			i  = (all->sprites_loc.coords[n].x - (all->textrs.spite.width / 2)) % all->textrs.spite.width;
//	else if (all->plr.ray.angle > 0 && all->plr.ray.angle < M_PI_4 ||
//				(all->plr.ray.angle > M_PI_4 + M_PI_2 + M_PI_2 + M_PI_2 && all->plr.ray.angle < M_PI + M_PI))
//			i  = (all->sprites_loc.coords[n].y - (all->textrs.spite.width / 2)) % all->textrs.spite.width;
//	else
//		return -1;

	return  i;
}

void	print_sprite_line(const t_all *all,int n, int high, int it, int i)
{
	float		ratio;
//	int			i;
	float		j;
	int			k;

	ratio = (float)high / (float)all->textrs.spite.width;
//	printf("%f\n", all->plr.ray.angle);

//	i  = -(all->sprites_loc.coords->x - (all->textrs.spite.width / 2)) % all->textrs.spite.width;
//	if (all->plr.ray.angle > 2.617993878 && all->plr.ray.angle < 3.665191429)
//		i *= -1;
	if (i == -1)
		return;
	j = 0;
	while ((int)j <high)
	{
		k = -1;
		while ((float)++k < ratio)
		{
//			if (all->textrs.spite.addr[(((int) all->textrs.spite.width * (int) (j / ratio)) + i + it)] == 0x000000)
//				continue;
//			if (((int) all->textrs.spite.width * (int) (j / ratio) + i + it) > all->textrs.spite.width * all->textrs.spite.width)
//				continue;
			if(((k + (int)j + (all->full_map->resolution.y >> 1) >= (high >> 1))) &&
			   (k + (int)j < (high >> 1) + (all->full_map->resolution.y >> 1)))
			{
				all->full_win.addr[(k + (int) j) * all->full_map->resolution.x + n +
									all->full_map->resolution.x *
									((all->full_map->resolution.y >> 1) - (int) (high >> 1))] =
						all->textrs.spite.addr[(((int) all->textrs.spite.width * (int) (j / ratio)) + it + i)];
			}
		}
		j += ratio;
	}
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

/*
int		curr_sprite_width(const t_all *all, float angle, int high)
{
	int		curr;
	float	left;
	float	right;
	float	high_angle;
	float	eps;

	left = 0;
	eps	= (float)(M_PI_6 + M_PI_6) / (float)all->full_map->resolution.x;
	high_angle = (float)high * eps;
	right = ABS(high_angle);
	angle += (high_angle / 2);
	curr = crossing_sprite(all, angle, &all->textrs.n_tex);
	while ((right - left) > eps)
	{
		if (curr == 1)
		{
			left += (right - left) / 2;
			angle += (right - left) / 2;
		}
		else
		{
			right -= (right - left) / 2;
			angle -= (right - left) / 2;
		}
		curr = crossing_sprite(all, angle, &all->textrs.n_tex);
	}
	return ABS((int)((left) / (float)(M_PI_6 + M_PI_6) * (float)all->full_map->resolution.x));
}
*/

//void dist_from_angle(const t_all *all, float *angle)
//{
//	t_point *sprite;
//	t_point plr;
//	int dx;
//	int dy;
//
//	sprite = all->sprites_loc.points;
//	plr.x = (int)(all->plr.x / 64);
//	plr.y = (int)(all->plr.y / 64);
//	dx = ABS(plr.x - sprite->x);
//	dy = ABS(plr.y - sprite->y);
//	*angle = sqrtf((float)(dx * dx + dy * dy));
//
//}

/*
int		add_sprite(const t_all *all, const t_sprites *sprite_data, float x_y) {
	int i;
	int n;
	float j;
	int high;
	float angle;
	i = -1;
	j = 0;
	while (++i <= sprite_data->size) {
		if(sprite_data->distns[i].dist < 1)
			continue;
		angle = sprite_data->distns[i].angle - all->plr.ray.angle;
//		dist_from_angle(all, &sprite_data->distns[i].dist);
//		high = (int)(x_y * all->full_map->resolution.y * all->textrs.spite.width / sprite_data->distns[i].dist);
//		if (high > all->full_map->resolution.y )
//			high = all->full_map->resolution.y;
//			continue;
		n = all->full_map->resolution.x / 2 * (1 + ( angle / ( M_PI_6)));

		float sp_step_step;
		all->sprites_loc.distns[i].width = curr_sprite_width(all, (sprite_data->distns[i].angle), high);

//		printf("%d\n", width);
		float sp_step = (float)high / all->textrs.spite.width;
		int kek = 0;
		while ((int)j < all->sprites_loc.distns[i].width  && (int)j + n < all->full_map->resolution.x)
		{
			sp_step_step = 0;
			while (sp_step_step < sp_step)
			{

				print_sprite_line(all, n + sp_step_step + j, high,  kek, find_i(all,i ));
				sp_step_step++;
			}
			kek++;
			j += sp_step;
		}

		j = 0;
	}
}
*/

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

void	add_sprite_line(t_all *all, int n, int repeat, int n_step)
{
	int i;
	int i_new;
	int sprite_col;
	sprite_col = (n_step);
//	printf("%d\n", n_step);
	i_new = 0;
	i = 0;
	while (i_new < all->textrs.spite.width)
	{
		all->full_win.addr[(n + all->full_map->resolution.x * (i + i_new * repeat) +
		(all->full_map->resolution.x - repeat * all->textrs.spite.width * 2) * all->full_map->resolution.y / 2)] =
				all->textrs.spite.addr[sprite_col + all->textrs.spite.width * i_new];
		i++;
		if (i >= repeat)
		{
			i_new++;
			i = 0;
		}
	}
}
void	add_sprite(t_all *all, int k, int n, int  high)
{
	int		it_k;
	int	repeat;
	float 	it_rep;
	float 	it_rep2;
	int		i;

	repeat = high / all->textrs.spite.width;
	it_k = 0;
	i = 0;
	while (it_k * repeat + i < k)
	{
		add_sprite_line(all, n + it_k * repeat + i, repeat, it_k);
		i++;
		if (i >= repeat)
		{
			i = 0;
			it_k++;
		}
	}

}

void	add_scale_line_sprite(const t_all *all, int n, int hign, const t_texture *textr, int i, t_sprite_dist_data *data)
{
//	int		i;
	float	ratio;
	int		k;
	float	j;
	int		max;

	ratio = (float)hign / (float)textr->width;
//	if(find_i(all, n))
//		i += (int)(data->y) % textr->width ;
//	else
//		i += (int)(data->x) % textr->width;
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
//			if (textr->addr[((int)textr->width * (int)(j / ratio)) + i] == 0)
//				continue;
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
	while (++i <= all->sprites_loc.size)
	{
		if (all->sprites_loc.distns->dist < 1)
			continue;
		angle_start = all->sprites_loc.distns[i].angle;
		spr_data = crossing_sprite(all, angle_start, &all->textrs.spite, &hehe);
		n = all->full_map->resolution.x / 2 * (1 + ( (angle_start - all->plr.ray.angle)/ ( M_PI_6)));
//		n = all->full_map->resolution.x / 2 * (1 + ((angle_start + M_PI_6) / (M_PI_6 + all->plr.ray.angle)));
//		printf("%f\t%f\n", angle_start, all->plr.ray.angle);
//		printf("%d\t%f\n",high, distns_sprite);
		k = 0;
		while (hehe != -1)
		{
			sprite_all_data[k] = spr_data;

			angle_start += (M_PI_6 + M_PI_6) / all->full_map->resolution.x;
			spr_data = crossing_sprite(all,angle_start,&all->textrs.spite, &hehe);
			k++;
		}
		ik = 0;
		int n_sprite;
		n_sprite = 0;

		float k_rep0 = (float)k / (float)all->textrs.spite.width;
		float k_rep = k_rep0;
		float k_rep_i = 0;
//		int	sprite_i = 0;
		high = (int)(x_y * (float)all->full_map->resolution.y * (float)all->textrs.spite.width /
					 ABS(sprite_all_data[k / 2].dist));
		while (ik < k && n < all->full_map->resolution.x && n_sprite < all->textrs.spite.width)
		{
			add_scale_line_sprite(all, n, high, &all->textrs.spite, n_sprite, sprite_all_data);
			ik++;
			k_rep_i++;
			if (k_rep_i >= k_rep)
			{
				k_rep += k_rep0;
//				k_rep_;
				n_sprite++;
			}
			n++;
		}
		/*
		while (distns_sprite != -1 && n < all->full_map->resolution.x)
		{
			is_x =  find_i(all, i);
			*//*if (is_x)
				k = cosf(angle_start);
			else
				k = sinf(angle_start);
			if (k == 0)
				k = 1;*//*
			add_scale_line(all, n, high, &all->textrs.spite, is_x);
			angle_start += (M_PI_6 + M_PI_6) / all->full_map->resolution.x;
			distns_sprite = crossing_sprite(all,angle_start,&all->textrs.spite);
			n++;
		}*/
	}
}

int     render_next_frame(t_all *all)
{
	add_flour(all);

	sprites_zero(all->sprites_loc.points);
	sprites_dist_sero(all->sprites_loc.distns);
	add_ray(all, &all->full_map->resolution, (float)all->full_map->resolution.x / all->full_map->resolution.y );
//	all->textrs.spite.angle = 0;
//	all->textrs.spite.k = 1;

//	distance_sprites(&all->sprts_crds, &all->plr, all->spr_distans,all->textrs.n_tex.width );
//	add_sprite(all, all->textrs.spite, all->textrs.n_tex.width);
	sprite_sort(all->sprites_loc.distns, all->sprites_loc.size);
//	add_sprite(all, &all->sprites_loc, (float)all->full_map->resolution.x / all->full_map->resolution.y);
	add_sprite_new(all);
	do_kek(all);
}


int	create_win(t_all *all)
{
//	t_win 	*win;

//	win = malloc(sizeof(t_win));
	all->full_win.win = mlx_new_window(all->full_win.mlx, all->full_map->resolution.x,
								  all->full_map->resolution.y, "cub3d");

	all->full_win.img = mlx_new_image(all->full_win.mlx, all->full_map->resolution.x,
							 all->full_map->resolution.y);
	all->full_win.addr = mlx_get_data_addr(all->full_win.img,
								  &all->full_win.bits_per_pixel,
								  &all->full_win.line_length,
								  &all->full_win.endian);
//	all->full_win = win;
//	render_next_frame(&all, &full_map);
	mlx_loop_hook(all->full_win.mlx, render_next_frame, &all->full_win);

	mlx_hook(all->full_win.win, 2, 1L << 0, key_commands, all);
//	render_next_frame(&all);

	mlx_loop(all->full_win.mlx);
}