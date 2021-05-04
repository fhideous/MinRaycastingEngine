#include "hdrs/cub3d.h"

int	find_crossing(t_all *all, float angle, int i, t_texture *txtr)
{
	t_ray	end;
	float	c;
	char	ch;

	c = (float)LEN_STEP;
	end.x = all->plr.x + c * cosf(angle);
	end.y = all->plr.y + c * sinf(angle);
	ch = all->f_map->map[(int)(end.y / (float)txtr->width)]
	[(int)(end.x / (float)txtr->width)];
	while (ch != '1')
	{
		end.x = all->plr.x + c * cosf(angle);
		end.y = all->plr.y + c * sinf(angle);
		c += (float)LEN_STEP;
		ch = all->f_map->map[(int)(end.y / (float)txtr->width)]
		[(int)(end.x / (float)txtr->width)];
	}
	all->plr.ray.x = end.x + (float)txtr->width / 2;
	all->plr.ray.y = end.y + (float)txtr->width / 2;
	all->plr.ray.len = c;
	if (i != -1)
		all->a_d_w[i] = c;
}

t_texture	texture_define(const t_ray *ray_new,
						 const t_textures *all_txtr, int *is_x)
{
	static t_ray	ray_old;
	t_texture		tmp_txtr;
	float			x_delt;
	float			y_delt;

	x_delt = ray_new->x - ray_old.x;
	y_delt = ray_new->y - ray_old.y;
	if (ABS(x_delt) - ABS(y_delt) > 0 && x_delt > 0)
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
	return (tmp_txtr);
}

int	check_max_choice_opposite(t_all *all, int is_x, int *max, int high)
{
	int	i;

	if (is_x)
		i = ((int)all->plr.ray.x - (all->ts.s_tex.width >> 1))
			% all->ts.s_tex.width;
	else
		i = ((int)all->plr.ray.y - (all->ts.s_tex.width >> 1))
			% all->ts.s_tex.width;
	*max = 0;
	if (high > all->f_map->res.y)
	{
		*max = (int)((high - all->f_map->res.y)) >> 1;
	}
	return (i);
}

void	add_scale_line(t_all *all, int n, int hign, int is_x)
{
	int		i;
	int		k;
	float	j;
	int		max;

	i = check_max_choice_opposite(all, is_x, &max, hign);
	j = 0;
	while ((int)j < hign + max)
	{
		k = 0;
		while (k - 1 < (int)((float)hign / (float)all->ts.c_t.width))
		{
			if (((k + (int)j + (all->f_map->res.y >> 1) >= (hign >> 1)))
				&& (k + (int)j < (hign >> 1) + (all->f_map->res.y >> 1)))
			{
				all->f_w.addr[(k + (int)j)*all->f_map->res.x + n
					+ all->f_map->res.x * ((all->f_map->res.y >> 1)
						- (hign >> 1))] = all->ts.c_t.addr[((all->ts.c_t.width
							 * (int)(j / ((float)hign
									/ (float)all->ts.c_t.width))) + i)];
			}
			k++;
		}
		j += ((float)hign / (float)all->ts.c_t.width);
	}
}

int	add_ray(t_all *all, const t_point *res, float x_y)
{
	float		angle;
	int			n;
	int			is_x;

	n = 0;
	angle = M_PI_6_N;
	while (n < res->x)
	{
		is_x = 0;
		all->ts.c_t = texture_define(&all->plr.ray, &all->ts, &is_x);
		find_crossing(all, all->plr.ray.angle + angle,
			n, &all->ts.c_t);
		all->a_d_w[n] = all->plr.ray.len;
		add_scale_line(all, n, (int)(x_y * (float)(res->y * all->ts.c_t.width)
				/ (all->plr.ray.len * (float)cos(angle))), is_x);
		n += 1;
		angle += (M_PI_6 + M_PI_6) / res->x;
	}
}
