#include "hdrs/cub3d.h"

int find_crossing(t_all *all, float  angle, int i, t_texture *txtr)
{
	t_ray	end;
	float	c;
	char	ch;

	c = (float)LEN_STEP;
	end.x = all->plr.x + c * cosf(angle);
	end.y  = all->plr.y + c * sinf(angle);
	ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
	[(int)(end.x / (float)txtr->width)];
	while (ch  != '1')
	{
		end.x = all->plr.x + c * cosf(angle);
		end.y  = all->plr.y + c * sinf(angle);
		c += (float)LEN_STEP;
		ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
		[(int)(end.x / (float)txtr->width)];
	}
	all->plr.ray.x = end.x + (float)txtr->width / 2;
	all->plr.ray.y = end.y + (float)txtr->width / 2;
	all->plr.ray.len = c;
	if (i != -1)
		all->all_distns_wall[i] = c;
}

t_texture texture_define(const t_ray *ray_new, const t_textures *all_txtr, int *is_x)
{
	static	t_ray	ray_old;
	t_texture		tmp_txtr;
	float			x_delt;
	float			y_delt;

	x_delt = ray_new->x - ray_old.x;
	y_delt = ray_new->y - ray_old.y;
	if(ABS(x_delt) - ABS(y_delt) > 0 && x_delt > 0)
	{
		tmp_txtr = all_txtr->s_tex;
		*is_x = 1;
	}
	else if (ABS(y_delt) - ABS(x_delt) > 0 && y_delt > 0)
		tmp_txtr = all_txtr->e_tex;
	else if (ABS(x_delt) - ABS(y_delt) > 0 && x_delt < 0)
	{
		tmp_txtr = all_txtr->n_tex;
		*is_x = 1;
	}
	else
		tmp_txtr = all_txtr->w_tex;
	ray_old = *ray_new;
	return tmp_txtr;
}


void	add_scale_line(const t_all *all, int n, int hign, const t_texture *textr, int is_x)
{
	int		i;
	float	ratio;
	int		k;
	float	j;
	int		max;

	ratio = (float)hign / (float)textr->width;
	if(is_x)
		i = ((int)all->plr.ray.x - (textr->width >> 1)) % textr->width ;
	else
		i = ((int)all->plr.ray.y - (textr->width >> 1)) % textr->width;
	j = 0;
	max = 0;
	if (hign > all->full_map->resolution.y)
	{
		max = (int)((hign - all->full_map->resolution.y)) >> 1;
	}
	while ((int)j < hign + max)
	{
		k = 0;
		while (k - 1 < (int)ratio)
		{
			if(((k + (int)j + (all->full_map->resolution.y >> 1) >= (hign >> 1))) &&
					(k + (int)j < (hign >> 1) + (all->full_map->resolution.y >> 1)))
			{
				all->full_win.addr[(k + (int)j) * all->full_map->resolution.x + n +
									all->full_map->resolution.x *
									((all->full_map->resolution.y >> 1) - (int)(hign >> 1))]  =
						textr->addr[(((int)textr->width * (int)(j / ratio)) + i)];
			}
			k++;
		}
		j += (ratio);
	}
}

int		add_ray(t_all *all, const t_point *res, float x_y)
{
	float	angle;
	float	k;
	int		n;
	float high;
	t_texture texture;
	int 	is_x;

	n = 0;
	angle = M_PI_6_N;
	while (n < res->x)
	{
		is_x = 0;
		k = cosf(angle);
		if (k == 0)
			k = 1;
		texture = texture_define(&all->plr.ray, &all->textrs, &is_x);
		find_crossing(all, all->plr.ray.angle + angle,
					  n, &texture);
		all->all_distns_wall[n] = all->plr.ray.len;

		high = x_y * (float)(res->y * texture.width) / (all->plr.ray.len * k) ;
		add_scale_line(all, n, (int)(high), &texture, is_x);

		n += 1;
		angle += (M_PI_6 + M_PI_6) / res->x;
	}
}
