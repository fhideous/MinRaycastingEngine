#include "hdrs/cub3d.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))

void find_crossing(t_all *all, float  angle, t_win *win, t_texture *txtr)
{
	t_ray end;
	float  c;

	c = (float)0.2;
	end.x = all->plr.x + c * cosf(angle);
	end.y  = all->plr.y + c * sinf(angle);
	while (all->full_map->map[(int)(end.y / (float)txtr->width)]
					[(int)(end.x / (float)txtr->width)] != '1')
	{
		end.x = all->plr.x + c * cosf(angle);
		end.y  = all->plr.y + c * sinf(angle);
		c += (float)ANGLE_STEP;
	}
	all->plr.ray.x = end.x + (float)txtr->width / 2;
	all->plr.ray.y = end.y + (float)txtr->width / 2;
	all->plr.ray.len = c;
}

t_texture texture_define(t_ray *ray_new, t_textures *all_txtr, int *is_x)
{
	static t_ray ray_old;
	t_texture	tmp_txtr;
	float		x_delt;
	float		y_delt;

	x_delt = ray_new->x - ray_old.x;
	y_delt = ray_new->y - ray_old.y;
	if(ABS(x_delt) > ABS(y_delt) && x_delt > 0)
	{
		tmp_txtr = all_txtr->s_tex;
		*is_x = 1;
	}
	else if (ABS(y_delt) > ABS(x_delt) && y_delt > 0)
		tmp_txtr = all_txtr->e_tex;
	else if (ABS(x_delt) > ABS(y_delt) && x_delt < 0)
	{
		tmp_txtr = all_txtr->n_tex;
		*is_x = 1;
	}
	else
		tmp_txtr = all_txtr->w_tex;
	ray_old = *ray_new;
	return tmp_txtr;
}

void	add_scale_line(t_all *all, int n, int hign, t_texture *textr, int is_x)
{
	int i ;
	float ratio;
	float k;
	float j;
	int cnt;

	ratio = (float)hign / textr->width;
	if(is_x)
		i = (int)all->plr.ray.x % textr->width;
	else
		i = (int)all->plr.ray.y % textr->width;
	cnt = 0;
	j = 0;
	while (j < hign && j < (float)all->full_map->resolution.y)
	{
		k = 0;
		while (k < ratio)
		{
			if(((int)(hign >> 1) <=  all->full_map->resolution.y >> 1) ||
					((k + j) > ABS((float)((all->full_map->resolution.y >> 1) - (int)(hign >> 1)))))
			{
				all->full_win->addr[(int)(k + j) * all->full_map->resolution.x + n - cnt  +
									all->full_map->resolution.x *
									((all->full_map->resolution.y >> 1) - (int)(hign >> 1))]  =
						textr->addr[(int) ((j * textr->width / ratio) + i )];

			}
			k ++;
		}
		j += (ratio);
	}
	i++;
	cnt++;
}

int		add_ray(t_all *all,const t_point *res)
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
		k = cos(angle);
		if (k == 0)
			k = 1;
//		if(all->plr.ray.len < 64)
//			continue;
		texture = texture_define(&all->plr.ray, &all->textrs, &is_x);
		find_crossing(all, all->plr.ray.angle + angle,
					  all->full_win, &texture);
		high = texture.width/ all->plr.ray.len * res->y / k * 1.7;
//		if(high > res->y)
//			high = 0;
		add_scale_line(all, n, (int)(high), &texture, is_x);

		n += 1;
		angle += 1.0 /res->x ;
	}
}
