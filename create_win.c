#include "hdrs/cub3d.h"
#include <math.h>

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

int find_i(const t_all *all, int n)
{
	int i;

	if (all->plr.ray.angle > M_PI_4 && all->plr.ray.angle < M_PI_4 + M_PI_2)
			i  = -(all->sprites_loc.coords[n].x - (all->textrs.spite.width / 2)) % all->textrs.spite.width;
	else if (all->plr.ray.angle > M_PI_4 + M_PI_2 && all->plr.ray.angle < M_PI_4 + M_PI_2 + M_PI_2)
			i  = -(all->sprites_loc.coords[n].y - (all->textrs.spite.width / 2)) % all->textrs.spite.width;
	else if (all->plr.ray.angle > M_PI_4 + M_PI_2  + M_PI_2 && all->plr.ray.angle < M_PI_4 + M_PI_2 + M_PI_2 + M_PI_2)
			i  = (all->sprites_loc.coords[n].x - (all->textrs.spite.width / 2)) % all->textrs.spite.width;
	else if (all->plr.ray.angle > 0 && all->plr.ray.angle < M_PI_4 ||
				(all->plr.ray.angle > M_PI_4 + M_PI_2 + M_PI_2 + M_PI_2 && all->plr.ray.angle < M_PI + M_PI))
			i  = (all->sprites_loc.coords[n].y - (all->textrs.spite.width / 2)) % all->textrs.spite.width;
	else
		return -1;
	return  i;
}

void	print_sprite_line(const t_all *all,int n, int high, int it, int i)
{
	float		ratio;
//	int			i;
	float		j;
	int			k;

	ratio = (float)high / (float)all->textrs.spite.width;
	printf("%f\n", all->plr.ray.angle);

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
			if (((int) all->textrs.spite.width * (int) (j / ratio) + i + it) > all->textrs.spite.width * all->textrs.spite.width)
				continue;
//			if(((k + (int)j + (all->full_map->resolution.y >> 1) >= (high >> 1))) &&
//			   (k + (int)j < (high >> 1) + (all->full_map->resolution.y >> 1)))
			{
				all->full_win->addr[(k + (int) j) * all->full_map->resolution.x + n +
									all->full_map->resolution.x *
									((all->full_map->resolution.y >> 1) - (int) (high >> 1))] =
						all->textrs.spite.addr[(((int) all->textrs.spite.width * (int) (j / ratio)) + i + it)];
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

int		crossing_sprite(const t_all *all, float angle, const t_texture *txtr)
{
	t_ray	end;
	float	c;
	char	ch;

	c = (float)LEN_STEP;
	end.x = all->plr.x + c * cosf(angle);
	end.y = all->plr.y + c * sinf(angle);
	ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
		 [(int)(end.x / (float)txtr->width)];
	while (ch != '1')
	{
		if (ch == '2')
			return 1;
		ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
			[(int)(end.x / (float)txtr->width)];
		end.x = all->plr.x + c * cosf(angle);
		end.y  = all->plr.y + c * sinf(angle);
		c += (float)LEN_STEP;
	}
	return  0;
}

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
		high = (int)(x_y * all->full_map->resolution.y * all->textrs.spite.width / sprite_data->distns[i].dist);
		if (high > all->full_map->resolution.y )
			high = all->full_map->resolution.y;
//			continue;
		n = all->full_map->resolution.x / 2 * (1 + ( angle / ( M_PI_6)));

		float sp_step_step;
		all->sprites_loc.distns[i].width = curr_sprite_width(all, (sprite_data->distns[i].angle), high);

//		printf("%d\n", width);
		float sp_step = (float)high / all->textrs.spite.width;
		int kek = 0;
		while ((int)j < all->sprites_loc.distns[i].width  && j + n < all->full_map->resolution.x)
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
	add_sprite(all, &all->sprites_loc, (float)all->full_map->resolution.x / all->full_map->resolution.y );
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