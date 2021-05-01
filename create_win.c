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

/*
t_sprite_dist_data crossing_sprite(const t_all *all, float angle, const t_texture *txtr, int *hehe, t_ray *sprite_pos)
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
		if (ch == '2' && (end.y / (float)txtr->width) == sprite_pos->x
		&& (end.x / (float)txtr->width) != sprite_pos->y)
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
*/

/*
float check_sprite_angle(const t_all *all, float angle, const t_texture *txtr, const t_ray *sprite_pos)
{
	t_ray	end;
	float	c;
	char	ch;

	c = (float)LEN_STEP;
	end.x = all->plr.x + c * cosf(angle);
	end.y = all->plr.y + c * sinf(angle);
	ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
	[(int)(end.x / (float)txtr->width)];

	while (ch != '2' || ((int)(end.y / (float)txtr->width) != (int)sprite_pos->x ||
			(int)(end.x / (float)txtr->width) != (int)sprite_pos->y))
//	while (ch != '2')
{
		if (c - sprite_pos->len > txtr->width)
		{
			return -1;
		}
		c += (float)LEN_STEP;
		end.x = all->plr.x + c * cosf(angle);
		end.y  = all->plr.y + c * sinf(angle);
		ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
		[(int)(end.x / (float)txtr->width)];
		if ((int)(end.x / (float)txtr->width) == 19)
		{c++;c--;}
	}


	return c;
}
*/

/*
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
*/

/*
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
*/

/*
void	add_sprite_new(t_all *all)
{
	float	angle_start;
	t_sprite_dist_data 	spr_data;
	int		i;
	int		n;
	float	high;
	float	x_y;
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
		angle_start = all->sprites_loc.angle_sprite_start[ i];
		float n_d_alpha = M_PI_3 / all->full_map->resolution.x;
		float sprite_dist_full;
		t_point sprite;
		float sprite_len = find_len_pif(all->plr, all->sprites_loc.points[i], all->textrs.spite.width);
		t_ray sprite_ray_costil;
		sprite = all->sprites_loc.points[i];
		sprite_ray_costil.y = sprite.y;
		sprite_ray_costil.x = sprite.x;
		sprite_ray_costil.len = sprite_len;
		sprite_dist_full = check_sprite_angle(all, angle_start - M_PI_3 / all->full_map->resolution.x, &all->textrs.n_tex, &sprite_ray_costil);

		j = 0;
		while (sprite_dist_full != -1 && j < 1920)
		{
			sprites_dist_full[j] = sprite_dist_full;
			n_d_alpha += M_PI_3 / all->full_map->resolution.x;
			sprite_dist_full = check_sprite_angle(all, angle_start - n_d_alpha , &all->textrs.n_tex, &sprite_ray_costil) ;
			j++;
		}
		n = all->full_map->resolution.x / 2 * (1 + ((angle_start - all->plr.ray.angle - n_d_alpha) / (M_PI_6)));
		spr_data = crossing_sprite(all, angle_start - n_d_alpha, &all->textrs.spite, &hehe, &sprite_ray_costil);
		int k = 0;
		float n_d_alpha_max = n_d_alpha;
		while ((hehe != -1  || n_d_alpha > 0) && k < 1920){
			sprite_all_data[k] = spr_data;
			k++;
			angle_start += (M_PI_6 + M_PI_6) / all->full_map->resolution.x;
			spr_data = crossing_sprite(all, angle_start - n_d_alpha_max, &all->textrs.spite, &hehe, &sprite_ray_costil);
			n_d_alpha -= M_PI_3 / all->full_map->resolution.x;
		}
		ik = 0;

		int n_sprite;
		n_sprite = 0;

		float	dist_for_high;
		dist_for_high = sprite_all_data[(int)(k -1) /2  ].dist ;
		dist_for_high +=sprites_dist_full[(j- 1) /2];
		dist_for_high /= 2;
		high =  (x_y * (float) all->full_map->resolution.y * (float) all->textrs.spite.width /
				 ABS(sprite_len));
		float k_rep0 = (float) high / (float)all->textrs.spite.width;
		float k_rep = k_rep0;
		float k_rep_i = 0;
		j = -1;

		while (sprites_dist_full[j + 1] != 0)
		{
			j++;
		}

		n_d_alpha = 0;
		float k_angle;
		while (ik <= k && n < all->full_map->resolution.x && n_sprite < all->textrs.spite.width)
		{
			if ( n > 0 ) {

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
*/

/*
float 	sprite_find(const t_all *all,const t_point *point, float angle)
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
		if (
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

	return c;
}
*/

/*
float find_len_pif(t_plr plr, t_point sprite, int width)
{
	float dx;
	float dy;
	float len;
//	printf("x\t%d y\t%d\t", (int)(plr.x / (float)width), (int)(plr.y / (float)width));
	dx = ((plr.x - 32 - (float)(sprite.y * width)));
	dy = (plr.y - 32 - (float)(sprite.x * width));
//	if (plr.ray.angle >= M_PI / 4 && plr.ray.angle <= 3 * M_PI /2)
//		dx -= 64;
//	if (dx > 0 && dy > 0)
//	{
//		dx -=width;
//	}
//	else if(dx < 0 && dy > 0)
//	{
//		dx -=width;
//	}
//	printf("%f\t%f\t%f\n", dx, dy, plr.ray.angle);
//	if (dy > 0) {
//		dx -= width;
//	}
//	printf("s_x\t%d s_y\t%d\t\t", sprite.y ,(sprite.x));

	len = sqrtf(dx*dx + dy*dy);
//	printf("%f\n", len);
	return (len);
}
*/


/*
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
*/

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
//		while (all->sprites_loc[i].angle - all->plr.ray.angle > M_PI)
//		{
//			all->sprites_loc[i].angle -= 2 * M_PI;
//		}
//		while (all->sprites_loc[i].angle - all->plr.ray.angle < -M_PI)
//		{
//			all->sprites_loc[i].angle += 2 * M_PI;
//		}
//		all->sprites_loc[i].angle += M_PI_2;
//		if (all->sprites_loc[i].angle < 0)
//			all->sprites_loc[i].angle += M_PI + M_PI;
//	if (all->sprites_loc[i].angle < 0)
//			all->sprites_loc[i].angle += M_PI + M_PI;

{
		all->sprites_loc[i].angle += M_PI;
		all->sprites_loc[i].angle += 3 * M_PI / 2;
		if(all->sprites_loc[i].angle > M_PI + M_PI)
			all->sprites_loc[i].angle -= (M_PI + M_PI);
		all->sprites_loc[i].angle *= -1;
		all->sprites_loc[i].angle += (M_PI + M_PI);
}
/*
		{
			while (all->sprites_loc[i].angle > M_PI_3)
				all->sprites_loc[i].angle -= M_PI_3;
			while (all->sprites_loc[i].angle < 0)
				all->sprites_loc[i].angle += M_PI_3;
		}
*/
//				printf("%d\t",  (int)(57.2958 * (all->sprites_loc[i].angle)));
//		printf("%d\n",  (int)(57.2958 * (all->plr.ray.angle)));

//		all->sprites_loc[i].angle = acosf((all->plr.x - (float)all->sprites_loc[i].coords.y * (float)all->textrs.n_tex.width) /
//									all->sprites_loc[i].dist) - all->plr.ray.angle;
//
		printf("%d\t%f\n", (int)(57.295779513* all->sprites_loc[i].angle), all->plr.ray.angle);

//		printf ("%d\t\n", (int)(57.295779513* (all->sprites_loc[i].angle - all->plr.ray.angle)));
		i++;
//		printf("%f\n", all->plr.ray.angle);

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
		j = 0;
		if (all->all_distns_wall[start.x + i] < all->sprites_loc[n].dist)
		{
			i++;
			continue;
		}
		while (j < high)
		{
				all->full_win.addr[start.x + i + (start.y + j) * all->full_map->resolution.x] = 0x000000;
			j++;
		}
//		printf("%d\n", start.x);
		i++;
//		printf ("%d\n",  (start.y + j) * all->full_map->resolution.x);
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
/*
	{

		high =  (x_y * (float) all->full_map->resolution.y * (float) all->textrs.spite.width /
				 all->sprites_loc[i].dist);
		start.y = all->full_map->resolution.x * (all->full_map->resolution.y / 2) - (int)(high/ 2);
		start.x = (int)((-all->sprites_loc[i].angle - plr_angle) * (float)(all->full_map->resolution.x) / (M_PI_3)) - ((int)high >> 1);
		while (i < all->full_map->resolution.x && start.y > 0)
		{
			all->full_win.addr[i + all->full_map->resolution.x * start.y] = 0xFF0000;
			all->full_win.addr[i + all->full_map->resolution.x * (start.y + (int)high)] = 0xFF0000;
			i++;
		}
	}
	*/
	i = -1;
	while (++i < all->size_sprites)
	{
		high =	(x_y * (float) all->full_map->resolution.y * (float) all->textrs.spite.width /
				 all->sprites_loc[i].dist);
		start.y =/* all->full_map->resolution.x * */(all->full_map->resolution.y / 2) - (int)(high/ 2);
		start.x = (int)((all->sprites_loc[i].angle - plr_angle) * (float)(all->full_map->resolution.x) / (M_PI_3)) - ((int)high >> 1);


//		printf("%d\t", start.x);
//		printf("%d\t%d\n", (int)(57.2958 * (all->sprites_loc[i].angle )),(int)(57.2958 * plr_angle) );
/*
		while (start.x >= all->full_map->resolution.x)
		{
			start.x -= all->full_map->resolution.x;
		}
*/
//		printf("%d\t", start.x);
//
/*
		while (start.x <= 0)
		{
			start.x += all->full_map->resolution.x;
		}
*/
//		printf("%d\n", start.x);
//		kek += i * 30;

//		printf("%d\t\t\t%d\n", start.x, start.y);
//		sprite_to_image(all, start, (int)high, i);

//		int i = 0;
/*		while (i < all->full_map->resolution.x && start.y > 0)
		{
			all->full_win.addr[i + all->full_map->resolution.x * start.y] = 0x0000FF;
			all->full_win.addr[i + all->full_map->resolution.x * (start.y + (int)high)] = 0x0000FF;
			i++;
		}
		i = 0;
		while (i < all->full_map->resolution.y)
		{
			all->full_win.addr[i * all->full_map->resolution.x + start.x] = 0x0000FF;
			all->full_win.addr[(i) * all->full_map->resolution.x + start.x + (int)high] = 0x0000FF;
			i++;
		}*/
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
